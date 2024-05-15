#include "Creep.h"
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
Creep::Creep(Vector2 position, Path* route, float speed, unsigned short hitPoints, const char* texture_path) : IGameObject({position.x, position.y, 1, 1}, 0) {
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
    if (hitPoints <= 0) index = route.size();
    if (index >= route.size()) {
        hitPoints = 0;
        IGameObject::remove(this);
        return;
    }
    if (CT::vec2Compare({body.x, body.y}, route[index], .9f)) {
        index++;
        if (index >= route.size()) return;
        float deltaX = body.x - route[index].x, deltaY = body.y - route[index].y;
        angle = atan2(deltaY, deltaX);
    }

    // please add speed
    body.x -= cos(angle) * speed * delta * 0.001f;
    body.y -= sin(angle) * speed * delta * 0.001f;
}

// void Creep::draw(float scale) {
//     std::cout << "Creep::draw\n";
//     if (!texture_.width)
//     {
//         DrawRectangleRec(
//             {body.x * scale, body.y * scale, body.width * scale, body.height * scale},
//             color
//         );
//         return;
//     }
//     DrawTexturePro(
//         texture,
//         {0, 0, (float)texture.width, (float)texture.height},
//         {body.x * scale, body.y * scale, body.width * scale, body.height * scale},
//         {body.width*scale*0.5f, body.height*scale*0.5f},
//         0.f,
//         color
//     );
// }

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

bool Creep::isCollidable() {
    return true;
}

float Creep::getSpeed() {
    return this->speed;
}

void Creep::hit(short damage) {
    if (this->hitPoints < damage || (!this->hitPoints)) {
        this->hitPoints = 0;
        return; 
    }
    this->hitPoints -= damage;
}

bool Creep::isDead() {
    return (this->hitPoints == 0);
}