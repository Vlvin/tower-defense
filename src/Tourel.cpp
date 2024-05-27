#include "Tourel.h"
#include "Creep.h"
#include "Bullet.h"
#include "Scene.h"
#include "Window.h"
#include <cmath>
#include <cstdio>
#include "ColorTools.h"



Tourel::Tourel(Scene& parent, Rectangle body, float projSpeed, float shootFreq, uint32_t layer) 
: IGameObject(parent, body, 0, layer), target(nullptr) {
    this->projSpeed = projSpeed;
    this->shootFreq = shootFreq;
    lastShot = GetTime();
}


void Tourel::update(float delta) {
    float actual_time = 0;
    if ((!target) || (CT::vec2Distance(this->getPosition(), target->getPosition()) > 4) || (target->getIsDead())) {
        target = nullptr;
        for (auto li = parent.begin(); li != parent.end(); li++) {
            if (!(*li)->isUpdatable()) continue;
            std::shared_ptr<IGameObject> object = 
                std::dynamic_pointer_cast<IGameObject>(*li);
            if ((!object->getIsCollideable()) || (object->getIsDead())) continue;
            auto creep = std::dynamic_pointer_cast<Creep>(object);
            if (!creep) continue;

            if ((CT::vec2Distance(this->getPosition(), creep->getPosition()) < 4.f)) {
                target = creep;
                break;
            }
        }
    }
    if (!target) return;
    
    float deltaX = target->getPosition().x - this->getPosition().x, 
          deltaY = target->getPosition().y - this->getPosition().y;

    angle = atan2(deltaY, deltaX);
    // algebra
        float a = 0., b = 0., c = 0., D = 0., t1 = 0., t2 = 0.;
        float targetAngle = (target)->getAngle();
        float targetConstantSpeed = (target)->getSpeed();
        float targetVelocityX = cos(targetAngle) * targetConstantSpeed;
        float targetVelocityY = sin(targetAngle) * targetConstantSpeed;
        float targetStartX = (target)->getPosition().x;
        float targetStartY = (target)->getPosition().y;
        float cannonX = this->getPosition().x;
        float cannonY = this->getPosition().y;

        a = pow(targetVelocityX, 2) + pow(targetVelocityY, 2) - pow(projSpeed, 2);
        b = 2 * (
                    targetVelocityX * (targetStartX - cannonX)
                    + targetVelocityY * (targetStartY - cannonY)
                );
        c = pow(targetStartX - cannonX, 2) + pow(targetStartY - cannonY, 2);
        D = pow(b, 2) - 4*a*c;
        t1 = (-b + sqrt(D))/(2*a);
        t2 = (-b - sqrt(D))/(2*a);
        actual_time = t1 > t2 ? t2 : t1;
        if (0. > t1) actual_time = t2;
        if (0. > t2) actual_time = t1;

        predX = targetStartX - (targetVelocityX * actual_time);
        predY = targetStartY - (targetVelocityY * actual_time);

        deltaX = this->getPosition().x - predX, 
        deltaY = this->getPosition().y - predY;

        angle = atan2(deltaY, deltaX);

    if (GetTime() - lastShot > shootFreq) {
        uint32_t bulletLayer = getDrawLayer() - 1;
        if (getDrawLayer() < 1) bulletLayer = 0;
        parent.add(std::make_shared<Bullet>(parent, getPosition(), 0.1, projSpeed, angle, 1, bulletLayer));
        lastShot = GetTime();
    }
}

void Tourel::draw(float scale, Vector2 camera) {
    float barrelX = ((body.x - camera.x) - (cos(angle)*0.5f*0.5f*body.width))*scale,
          barrelY = ((body.y - camera.y) - (sin(angle)*0.5f*0.25f*body.height))*scale,
          barrelWidth = scale,
          barrelHeight = scale*0.5f;
    DrawRectanglePro(
        (Rectangle){
            barrelX + Window::getInstance()->getSize().x*0.5f,
            barrelY + Window::getInstance()->getSize().y*0.5f, 
            barrelWidth, barrelHeight
        }, 
        {scale*0.5f, 0.5f*scale*0.5f}, 
        this->angle/M_PI*180, 
        GRAY);
    IGameObject::draw(scale, camera);
    DrawCircleLines(
        (body.x - camera.x)*scale + Window::getInstance()->getSize().x*0.5f, 
        (body.y - camera.y)*scale + Window::getInstance()->getSize().y*0.5f, 
        4.f*scale, 
        PINK
    );
    if (!target) return;
    
    DrawRectangleLines(
        (target->getPosition().x - camera.x)*scale-0.5f*scale + Window::getInstance()->getSize().x*0.5f, 
        (target->getPosition().y - camera.y)*scale-0.5f*scale + Window::getInstance()->getSize().y*0.5f, 
        scale, 
        scale,
        GREEN
    );

}
void Tourel::cleanUp() {
}