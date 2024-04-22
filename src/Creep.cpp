#include "Creep.h"
#include "ColorTools.h"
#include <cmath>
#include <cstdio>


std::vector<std::shared_ptr<Creep>> Creep::all;

/**
 * @param[in] route Path node pointing to any cell of route (if you got it after Path::setRouteFromStart)
 * @param[in] position Spawn position
 * @warning route must be not cycling
*/
Creep::Creep(Vector2 position, Path* route, float speed) : IGameObject({position.x, position.y, 0.5, 0.5}, 0) {
    this->speed = speed;
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
    all.push_back(std::shared_ptr<Creep>(this));
}



void Creep::update(float delta) {
    if (index >= route.size()) return;
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

std::shared_ptr<Creep> Creep::get(long index) {
    if (index >= Creep::all.size()) 
        return nullptr;
    return Creep::all[index];
}

void Creep::clearAtEnd() {
    for (int i = 0; i < Creep::all.size(); i++) {
        if (Creep::get(i)->isAtEnd()) {
            // delete Creep::get(i);
            Creep::all[i] = Creep::all.back();
            Creep::all.pop_back();
        }
    }
}

void Creep::drawAll(float scale) {
    for (int i = 0; i < Creep::all.size(); i++) {
        (Creep::get(i))->draw(scale);
    }
}

void Creep::updateAll(float delta) {
    for (int i = 0; i < Creep::all.size(); i++) {
        (Creep::get(i))->update(delta);
    }
}

void Creep::cleanUp() {
    while (Creep::count())
        Creep::pop();
}

long Creep::count() {
    return Creep::all.size();
}

std::shared_ptr<Creep> Creep::pop() {
    std::shared_ptr<Creep> res = all.back();
    all.pop_back();
    return res;
}

float Creep::getSpeed() {
    return this->speed;
}