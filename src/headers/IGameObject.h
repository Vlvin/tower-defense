#pragma once 
#include <raylib.h>
#include <memory>

class Scene;

class IGameObject {
protected:
    Scene& parent;
    Rectangle body;
    bool isDead;
    bool isCollideable;
    Texture2D texture;
    float angle;
    Color color;
public:
    IGameObject(Scene& parent, Rectangle body, float angle, bool collideable = false);
    virtual void update(float delta) = 0;
    virtual bool getIsCollideable();
    virtual void draw(float scale, Vector2 camera);
    bool getIsDead();
    void setColor(Color color);
    Vector2 getPosition();
    Rectangle getBody();
    float getAngle();
};