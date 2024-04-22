#pragma once

#include "IGameObject.h"
#include <memory>
#include <vector>

class Creep;

class Tourel: public IGameObject {
    static std::vector<std::shared_ptr<Tourel>> all;
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
    static void drawAll(float scale);
    static void updateAll(float delta);
    static void cleanUp();
    static long count();
    static std::shared_ptr<Tourel> get(long index);
};