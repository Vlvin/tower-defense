#pragma once 
#include <raylib.h>

class IGameObject {
protected:
    Rectangle body;
    float angle;
public:
    IGameObject(Rectangle body, float angle);
    virtual void update(float delta) = 0;
    virtual void draw(float scale);
    Vector2 getPosition();
    float getAngle();
};