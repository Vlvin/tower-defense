#pragma once
#include "IGameObject.h"
#include <memory>
#include <vector>
#include <list>

class Bullet : public IGameObject {
protected:
    uint16_t damage;
    float speed, radius;
public:
    Bullet(Scene& parent, Vector2 position, float radius, float speed, float angle, uint16_t damage = 1, uint32_t layer = 2);
    virtual void update(float delta) override;
    virtual void draw(float scale, Vector2 camera) override;
    float getSpeed();
    uint16_t getDamage();
    static void cleanUp();
};