#include "Creep.h"
#include "ColorTools.h"
#include <cmath>
#include <cstdio>

/**
 * @param[in] route Path node pointing to any cell of route (if you got it after Path::setRouteFromStart)
 * @param[in] position Spawn position
 * @warning route must be not cycling
*/
Creep::Creep(Vector2 position, Path* route, float speed) {
    this->position = position;
    this->speed = speed;
    Path* i = route;
    while (i->getPrevious() != nullptr)
        i = i->getPrevious();
    while(i != nullptr) {
        this->route.push_back(i->getPosition());
        i = i->getNext();
    }
    this->index = 0;
    float deltaX = position.x - this->route[index].x, deltaY = position.y - this->route[index].y;
    angle = atan2(deltaY, deltaX); 
}



void Creep::update(float delta) {
    if (index >= route.size()) return;
    if (CT::vec2Compare(position, route[index], 1.001f)) {
        index++;
        if (index >= route.size()) return;
        float deltaX = position.x - route[index].x, deltaY = position.y - route[index].y;
        angle = atan2(deltaY, deltaX);
    }


    // please add speed
    position.x -= cos(angle) * speed * delta * 0.001f;
    position.y -= sin(angle) * speed * delta * 0.001f;
}

void Creep::draw(float scale) { 
    DrawRectangle(position.x*scale, position.y*scale, scale, scale, BROWN);
}

Vector2 Creep::getPosition() {
    return position;
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