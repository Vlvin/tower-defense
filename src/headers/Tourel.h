#pragma once

#include "IGameObject.h"
#include <memory>
#include <vector>

class Creep;

class Tourel: public IGameObject {
protected:
    float projSpeed;
    float shootFreq;
    float lastShot;
    float predX, predY;
    Creep* target;
public:
    Tourel(Rectangle body, float projSpeed, float shootFreq);
    virtual void update(float delta) override;
    virtual void draw(float scale, Vector2 camera) override;
    virtual bool isCollidable() override;
    static void cleanUp();
};