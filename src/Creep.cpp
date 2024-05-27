#include "Creep.h"
#include "Scene.h"
#include "Bullet.h"
#include "ColorTools.h"
#include <cmath>
#include <cstdio>
#include <iostream>

Texture2D Creep::texture_{0, 0};

/**
 * @param[in] route Path node pointing to any cell of route (if you got it after Path::setRouteFromStart)
 * @param[in] position Spawn position
 * @warning route must be not cycling
*/
Creep::Creep(Scene& parent, Vector2 position, Path* route, float speed, uint16_t hitPoints, const char* texture_path, uint32_t layer) 
: IGameObject(parent, {position.x, position.y, 1, 1}, 0, true, layer) {
    this->speed = speed;
    this->hitPoints = hitPoints;
    Path* i = route;
    while (i->getPrevious() != nullptr)
        i = i->getPrevious();
    while(i != nullptr) {
        this->route.push_back({i->getPosition().x+0.5f, i->getPosition().y+0.5f});
        i = i->getNext();
    }
    this->index = 0;
    float deltaX = position.x - this->route[index].x, deltaY = position.y - this->route[index].y;
    angle = atan2(deltaY, deltaX); 
    texture = texture_;
    if ((!texture_path)) return;
    if (texture_.width > 0) return;
    Image temp = LoadImage(texture_path);
    texture = texture_ = LoadTextureFromImage(temp);
    UnloadImage(temp);
}



void Creep::update(float delta) {
    if ((hitPoints <= 0) || (index >= route.size())) {
        isDead = true;
        return;
    }
    if (CT::vec2Compare({body.x, body.y}, route[index], .9f)) {
        index++;
        if (index >= route.size()) return;
        float deltaX = body.x - route[index].x, deltaY = body.y - route[index].y;
        angle = atan2(deltaY, deltaX);
    }
    for (auto li = parent.begin(); li != parent.end(); li++) {
        if (!(*li)->isUpdatable()) continue;
        std::shared_ptr<IGameObject> object = 
            std::dynamic_pointer_cast<IGameObject>(*li);
        if ((!object->getIsCollideable())) continue;
        auto bullet = std::dynamic_pointer_cast<Bullet>(object);
        if (!bullet) continue;
        float x = bullet->getBody().x, y = bullet->getBody().y, radius = bullet->getBody().width;
        if (CT::isCircleInBox2({x, y}, radius, this->body, 10.f)) {
            std::cout << "Zombie " << this << " hp: " << this->hitPoints << '\n';
            // this->hit(bullet->getDamage());
        }
    }

    // please add speed
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
}

Vector2 Creep::getTarget() {
    if (index >= route.size()) return {-14.f, -88.f};
    return route[index];
}

int Creep::getIndex() {
    return index;
}

bool Creep::isAtEnd() {
    return index >= route.size();
}

void Creep::cleanUp() {
    UnloadTexture(texture_);
}

float Creep::getSpeed() {
    return this->speed;
}

void Creep::hit(uint16_t damage) {
    std::cout << this << " hp: " << hitPoints << '\n';
    if (this->hitPoints < damage || (!this->hitPoints)) {
        this->hitPoints = 0;
        return; 
    }
    this->hitPoints -= damage;
}