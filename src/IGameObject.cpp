#include "IGameObject.h"
#include <cmath>


IGameObject::IGameObject(Rectangle body, float angle) {
    this->body = body;
    this->angle = angle;
}

void IGameObject::draw(float scale) {
    DrawRectanglePro({body.x*scale, body.y*scale, body.width*scale, body.height*scale}, {0.5f*scale, 0.5f*scale}, this->angle/M_PI*180, BROWN);
}

Vector2 IGameObject::getPosition() {
    return {body.x, body.y};
}

float IGameObject::getAngle() {
    return angle;
}