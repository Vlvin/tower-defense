#include "Tourel.h"
#include "Creep.h"
#include "Bullet.h"
#include <cmath>
#include <cstdio>
#include "ColorTools.h"


Tourel::Tourel(Rectangle body, float projSpeed, float shootFreq) : IGameObject(body, 0) {
    this->projSpeed = projSpeed;
    this->shootFreq = shootFreq;
    this->target = nullptr;
    this->lastShot = GetTime();
}


void Tourel::update(float delta) {
    float actual_time = 0;
    if ((this->target == nullptr) || (CT::vec2Distance(this->getPosition(),this->target->getPosition()) > 1)) {
       this->target = nullptr;
        for (int i = 0; i < Creep::count(); i++) {
            std::shared_ptr<Creep> creep = Creep::get(i);
            if (CT::vec2Distance(this->getPosition(), creep->getPosition()) < 4.f) {
                this->target = std::shared_ptr<Creep>(creep);
                break;
            }
        }
    }
    if (this->target == nullptr) return;
    
    float deltaX =this->target->getPosition().x - this->getPosition().x, 
          deltaY =this->target->getPosition().y - this->getPosition().y;

    angle = atan2(deltaY, deltaX);
    // algebra
        float a = 0., b = 0., c = 0., D = 0., t1 = 0., t2 = 0.;
        float targetAngle = (this->target)->getAngle();
        float targetConstantSpeed = (this->target)->getSpeed();
        float targetVelocityX = cos(targetAngle) * targetConstantSpeed;
        float targetVelocityY = sin(targetAngle) * targetConstantSpeed;
        float targetStartX = (this->target)->getPosition().x;
        float targetStartY = (this->target)->getPosition().y;
        float cannonX = this->getPosition().x;
        float cannonY = this->getPosition().y;
            
        
        if (cos(targetAngle) * targetConstantSpeed != targetVelocityX) 
            printf("!!!! %f != %f\n", targetVelocityX, cos(targetAngle) * targetConstantSpeed);

        a = pow(targetVelocityX, 2) + pow(targetVelocityY, 2) - pow(projSpeed, 2);
        b = 2 * (
                    targetVelocityX * (targetStartX - cannonX)
                    + targetVelocityY * (targetStartY - cannonY)
                );
        c = pow(targetStartX - cannonX, 2) + pow(targetStartY - cannonY, 2);
        D = pow(b, 2) - 4*a*c;
        printf("a:%f b:%f c:%f D:%f\n", a, b, c, D);
        t1 = (-b + sqrt(D))/(2*a);
        t2 = (-b - sqrt(D))/(2*a);
        actual_time = t1 > t2 ? t2 : t1;
        if (0. > t1) actual_time = t2;
        if (0. > t2) actual_time = t1;
        printf("Time  %f:%f  %f\n", t1, t2, actual_time);

        predX = targetStartX - (targetVelocityX * actual_time);
        predY = targetStartY - (targetVelocityY * actual_time);

        deltaX = this->getPosition().x - predX, 
        deltaY = this->getPosition().y - predY;
        printf("Position predicted %f:%f target Start %f:%f delta  %f:%f  speed %f  %f:%f angle %f\n"
                "cos %f sin %f\n", 
            predX, predY, targetStartX, targetStartY, deltaX, deltaY, 
            targetConstantSpeed, targetVelocityX, targetVelocityY,
            targetAngle, cos(targetAngle), sin(targetAngle));

        angle = atan2(deltaY, deltaX);

    if (GetTime() - lastShot > shootFreq) {
        new Bullet(getPosition(), 0.1, projSpeed, angle);
        lastShot = GetTime();
    }
}

void Tourel::draw(float scale) {
    IGameObject::draw(scale);
    DrawCircleLines(this->getPosition().x*scale,this->getPosition().y*scale, 4.f*scale, PINK);
    if (!target) return;
    DrawRectanglePro(
        {this->target->getPosition().x*scale, this->target->getPosition().y*scale, 0.5f*scale, 0.5f*scale},
        {0.5f*0.5f*scale, 0.5f*0.5f*scale},
        this->target->getAngle()/M_PI*180.,
        RED
    );
    DrawRectanglePro(
        {predX*scale, predY*scale, 0.5f*scale, 0.5f*scale},
        {0.5f*0.5f*scale, 0.5f*0.5f*scale},
        this->target->getAngle()/M_PI*180.,
        DARKPURPLE
    );
}