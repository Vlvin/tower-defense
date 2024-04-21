#include "Tourel.h"
#include "Creep.h"
#include "Bullet.h"
#include <cmath>
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
            if (CT::vec2Distance(this->getPosition(), creep->getPosition()) <= 1) {
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
    float a, b, c, D, t1, t2,
    tSpeed =this->target->getSpeed(),
    tVelX = cos(angle) * delta * tSpeed * 0.001f,
    tVelY = sin(angle) * delta * tSpeed * 0.001f,
    tStartX =this->target->getPosition().x,
    tStartY =this->target->getPosition().y,
    cannonX =this->target->getPosition().x,
    cannonY =this->target->getPosition().y;

    a = pow(tVelX, 2) + pow(tVelY, 2) - pow(projSpeed, 2);
    b = 2 * (
        tVelX * (tStartX - cannonX)
        + tVelY * (tStartY - cannonY));
    c = pow(tStartX - cannonX, 2) + pow(tStartY - cannonY, 2);
    D = sqrt(b) - 4*a*c;
    t1 = (-b + sqrt(D))/(2*a);
    t2 = (-b - sqrt(D))/(2*a);
    actual_time = t1 > t2? t2: t1;
    if (0. == D) actual_time = t1;
    if (0. > t1) actual_time = t2;
    if (0. > t2) actual_time = t1;



    float predX, predY;
    predX = tStartX + (tVelX * actual_time);
    predY = tStartY + (tVelY * actual_time);

    deltaX = predX - this->getPosition().x, 
    deltaY = predY - this->getPosition().y;

    angle = atan2(deltaY, deltaX);

    if (GetTime() - lastShot > shootFreq) {
        new Bullet(getPosition(), 0.2, projSpeed, angle);
        lastShot = GetTime();
    }
}

void Tourel::draw(float scale) {
    IGameObject::draw(scale);
    if (!target) return;
    DrawRectanglePro(
        {target->getPosition().x*scale,this->target->getPosition().y*scale, 0.25f*scale, 0.25f*scale},
        {0.5f*scale, 0.5f*scale},
       this->target->getAngle(),
        RED
    );
}