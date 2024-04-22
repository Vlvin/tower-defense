#include "Bullet.h"
#include "ColorTools.h"
#include "Creep.h"
#include <cmath>
#include <cstdio>

std::list<std::shared_ptr<Bullet>> Bullet::all;

Bullet::Bullet(Vector2 position, float radius, float speed, float angle, unsigned short damage) 
: IGameObject({position.x, position.y, radius, radius}, angle) {
    this->speed = speed;
    this->damage = damage;
    this-> radius = radius;
    all.push_back(std::shared_ptr<Bullet>(this));

}

void Bullet::update(float delta) {
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
    for (long i = 0; i < Creep::count(); i++) {
        if (CT::isCircleInBox2({body.x, body.y}, this->radius, Creep::get(i)->body, 5.f)) {
            Creep::get(i)->hit(this->damage);
            printf("%u\n", Creep::get(i)->hitPoints);
            this->damage = 0;
            break;
        }
    }
}

void Bullet::draw(float scale) {
    DrawCircle(body.x*scale, body.y*scale, radius*scale, BLACK);
}

float Bullet::getSpeed() {
    return this->speed;
}

void Bullet::cleanUp() {
    while (!Bullet::all.empty())
        Bullet::all.pop_back();
}

long Bullet::count() {
    return Bullet::all.size();
}

std::shared_ptr<Bullet> Bullet::get(long index) {
    if ((index >= Bullet::all.size()) || (index < 0)) return nullptr;
    std::shared_ptr<Bullet> result = nullptr;
    long i = 0;
    for (auto ii = Bullet::all.begin(); ii != Bullet::all.end(); ii++) {
        if (i == index) {
            result = *ii;
            break;
        }
        i++;
    }
    return result;
}

void Bullet::drawAll(float scale) {
    for (int i = 0; i < Bullet::all.size(); i++) {
        (Bullet::get(i))->draw(scale);
    }
}

std::shared_ptr<Bullet> Bullet::pop() {
    std::shared_ptr<Bullet> res = all.back();
    all.pop_back();
    return res;
}

void Bullet::updateAll(float delta) {
    for (auto ii = Bullet::all.begin(); ii != Bullet::all.end(); ii++) {
        (*ii)->update(delta);
        if ((*ii)->damage <= 0) {
            Bullet::all.remove(*ii++);
        }
    }
}