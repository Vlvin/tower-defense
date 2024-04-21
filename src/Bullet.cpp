#include "Bullet.h"
#include <cmath>

std::vector<std::shared_ptr<Bullet>> Bullet::all;

Bullet::Bullet(Vector2 position, float radius, float speed, float angle) 
: IGameObject({position.x, position.y, radius, radius}, angle) {
    this->speed = speed;
    this-> radius = radius;
    all.push_back(std::shared_ptr<Bullet>(this));

}

void Bullet::update(float delta) {
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
}

void Bullet::draw(float scale) {
    DrawCircle(body.x*scale, body.y*scale, radius*scale, RED);
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
    return Bullet::all[index];
}

void Bullet::drawAll(float scale) {
    for (int i = 0; i < Bullet::all.size(); i++) {
        (Bullet::get(i))->draw(scale);
    }
}

void Bullet::updateAll(float delta) {
    for (int i = 0; i < Bullet::all.size(); i++) {
        (Bullet::get(i))->update(delta);
    }
}