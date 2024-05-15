#pragma once
#include "IGameObject.h"
#include <memory>
#include <vector>
#include <list>

class Bullet : public IGameObject {
protected:
    unsigned short damage;
    float speed, radius;
public:
    Bullet(Vector2 position, float radius, float speed, float angle, unsigned short damage = 1);
    virtual void update(float delta) override;
    virtual void draw(float scale, Vector2 camera) override;
    float getSpeed();
    virtual bool isCollidable();
    static void cleanUp();
};