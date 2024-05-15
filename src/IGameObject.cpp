#include "IGameObject.h"
#include "Window.h"
#include <cmath>
#include <iostream>

std::list<IGameObject*> IGameObject::all;
std::list<IGameObject*> IGameObject::removals;

IGameObject::IGameObject(Rectangle body, float angle) {
    this->body = body;
    this->angle = angle;
    this->color = WHITE;
    texture.width = 0;
    all.push_back(this);
}

void IGameObject::draw(float scale, Vector2 camera) {
    if (texture.width <= 0) {
        DrawRectanglePro(
            {
                (body.x-camera.x)*scale + Window::getInstance()->getSize().x * 0.5f, 
                (body.y-camera.y)*scale + Window::getInstance()->getSize().y * 0.5f, 
                body.width*scale, 
                body.height*scale}, 
            {body.width*0.5f*scale, body.height*0.5f*scale}, 
            this->angle/M_PI*180, color);
        return;
    }
    DrawTexturePro(
        texture, 
        (Rectangle){0, 0, texture.width, texture.height}, 
        {
            (body.x-camera.x)*scale + Window::getInstance()->getSize().x * 0.5f, 
            (body.y-camera.y)*scale + Window::getInstance()->getSize().y * 0.5f, 
            body.width*scale, 
            body.height*scale}, {body.width*0.5f*scale, body.height*0.5f*scale}, this->angle/M_PI*180-90, color);
}

void IGameObject::remove(IGameObject* obj) {
    removals.push_back(obj);
    for (auto li = begin(); li != end(); li++) {
        if ((*li) == obj) {
            *li = all.back();
            all.pop_back();
        }
    }
}

std::list<IGameObject*>::iterator IGameObject::begin() {
    return all.begin();
}

std::list<IGameObject*>::iterator IGameObject::end() {
    return all.end();
}

void IGameObject::updateAll(float deltaTime) {
    while (!removals.empty()) {
        delete removals.back();
        removals.pop_back();
    }
    for (auto li = all.begin(); li != all.end(); li++) {
        (*li)->update(deltaTime);
    }
}
void IGameObject::drawAll(float scale, Vector2 camera) {
    for (auto li = all.begin(); li != all.end(); li++) {
        (*li)->draw(scale, camera);
    }
}

void IGameObject::setColor(Color color) {
    this->color = color;
}

Vector2 IGameObject::getPosition() {
    return {body.x, body.y};
}

float IGameObject::getAngle() {
    return angle;
}

void IGameObject::cleanUp() {
    while (!all.empty()) {
        delete all.back();
        all.pop_back();
    }
}