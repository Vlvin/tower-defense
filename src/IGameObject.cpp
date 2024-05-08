#include "IGameObject.h"
#include <cmath>


IGameObject::IGameObject(Rectangle body, float angle) {
    this->body = body;
    this->angle = angle;
    texture.width = 0;
}

void IGameObject::draw(float scale) {
    if (texture.width <= 0) {
        DrawRectanglePro({body.x*scale, body.y*scale, body.width*scale, body.height*scale}, {body.width*0.5f*scale, body.height*0.5f*scale}, this->angle/M_PI*180, RED);
        return;
    }
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height}, {body.x*scale, body.y*scale, body.width*scale, body.height*scale}, {body.width*0.5f*scale, body.height*0.5f*scale}, this->angle/M_PI*180-90, WHITE);
}

Vector2 IGameObject::getPosition() {
    return {body.x, body.y};
}

float IGameObject::getAngle() {
    return angle;
}