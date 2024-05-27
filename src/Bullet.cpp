#include "Bullet.h"
#include "Window.h"
#include "Scene.h"
#include "ColorTools.h"
#include "Creep.h"
#include <cmath>
#include <cstdio>


Bullet::Bullet(Scene& parent, Vector2 position, float radius, float speed, float angle, unsigned short damage) 
: IGameObject(parent, {position.x, position.y, radius, radius}, angle, true) {
    this->speed = speed;
    this->damage = damage;
    this->radius = radius;

}

void Bullet::update(float delta) {
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
    for (auto li = parent.begin(); li != parent.end(); li++) {
        if (!(*li)->isUpdatable()) continue;
        std::shared_ptr<IGameObject> object = 
            std::dynamic_pointer_cast<IGameObject>(*li);
        if ((!object->getIsCollideable()) || (object->getIsDead())) continue;
        auto creep = std::dynamic_pointer_cast<Creep>(object);
        if (!creep) continue;

        if (CT::isCircleInBox2({body.x, body.y}, this->radius, creep->getBody(), 10.f)) {
            creep->hit(getDamage());
            this->isDead = true;
            return;
        }
    }
}

void Bullet::draw(float scale, Vector2 camera) {
    DrawCircle(
        (body.x - camera.x)*scale + Window::getInstance()->getSize().x*0.5f, 
        (body.y - camera.y)*scale + Window::getInstance()->getSize().y*0.5f, 
        radius*scale, BLACK
    );
}

unsigned short Bullet::getDamage() {
    return this->damage;
}

float Bullet::getSpeed() {
    return this->speed;
}