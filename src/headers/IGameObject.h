#pragma once 
#include <raylib.h>
#include <memory>
#include "Node.h"

class Scene;

class IGameObject : public Node {
protected:
    // Scene& parent;
    Rectangle body;
    bool isDead;
    bool isCollideable;
    Texture2D texture;
    float angle;
    Color color;
public:
    IGameObject(Scene& parent, Rectangle body, float angle, bool collideable = false, uint32_t layer = 1);
    // virtual void update(float delta) = 0;
    virtual bool isUpdatable() override;
    virtual bool getIsCollideable();
    virtual void draw(float scale, Vector2 camera) override;
    bool getIsDead();
    void setColor(Color color);
    Vector2 getPosition();
    Rectangle getBody();
    float getAngle();
};