#pragma once 
#include <raylib.h>

class IGameObject {
protected:
    Rectangle body;
    Texture2D texture;
    float angle;
    Color color;
public:
    IGameObject(Rectangle body, float angle);
    virtual void update(float delta) = 0;
    virtual void draw(float scale);
    void setColor(Color color);
    Vector2 getPosition();
    float getAngle();
};