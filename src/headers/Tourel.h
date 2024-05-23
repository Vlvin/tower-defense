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
    std::shared_ptr<Creep> target;
public:
    Tourel(Scene& parent, Rectangle body, float projSpeed, float shootFreq);
    virtual void update(float delta) override;
    virtual void draw(float scale, Vector2 camera) override;
    static void cleanUp();
};