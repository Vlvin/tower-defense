#include "IGameObject.h"
#include "Window.h"
#include <cmath>
#include <iostream>

IGameObject::IGameObject(Scene& parent, Rectangle body, float angle, bool collideable) : parent(parent) {
    this->body = body;
    this->angle = angle;
    this->color = WHITE;
    isCollideable = collideable;
    isDead = false;
    texture.width = 0;

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

void IGameObject::setColor(Color color) {
    this->color = color;
}

Vector2 IGameObject::getPosition() {
    return {body.x, body.y};
}

Rectangle IGameObject::getBody() {
    return body;
}

float IGameObject::getAngle() {
    return angle;
}

bool IGameObject::getIsDead() {
    return isDead;
}

bool IGameObject::getIsCollideable() {
    return isCollideable;
}