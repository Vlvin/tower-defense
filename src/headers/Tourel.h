#pragma once

#include "IGameObject.h"
#include <memory>

class Creep;

class Tourel: public IGameObject {
protected:
    float projSpeed;
    float shootFreq;
    float lastShot;
    float predX, predY;
    std::shared_ptr<Creep> target;
public:
    Tourel(Rectangle body, float projSpeed, float shootFreq);
    virtual void update(float delta) override;
    virtual void draw(float scale) override;
};