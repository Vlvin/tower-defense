#include "Bullet.h"
#include "Window.h"
#include "ColorTools.h"
#include "Creep.h"
#include <cmath>
#include <cstdio>


Bullet::Bullet(Vector2 position, float radius, float speed, float angle, unsigned short damage) 
: IGameObject({position.x, position.y, radius, radius}, angle) {
    this->speed = speed;
    this->damage = damage;
    this->radius = radius;

}

void Bullet::update(float delta) {
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
    for (auto li = IGameObject::begin(); li != IGameObject::end(); li++) {

        if (!(*li)->isCollidable()) continue;
        Creep* creep = dynamic_cast<Creep*>(*li);
        if (!creep) continue;

        if (CT::isCircleInBox2({body.x, body.y}, this->radius, creep->body, 5.f)) {
            creep->hit(this->damage);
            printf("%u\n", creep->hitPoints);
            this->damage = 0;
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

float Bullet::getSpeed() {
    return this->speed;
}

bool Bullet::isCollidable() {
    return true;
}