#pragma once
#include "IGameObject.h"
#include <memory>
#include <vector>
#include <list>

class Bullet : public IGameObject {
private:
    static std::list<std::shared_ptr<Bullet>> all;
    static std::shared_ptr<Bullet> pop();
protected:
    unsigned short damage;
    float speed, radius;
public:
    Bullet(Vector2 position, float radius, float speed, float angle, unsigned short damage = 1);
    virtual void update(float delta) override;
    virtual void draw(float scale) override;
    float getSpeed();
    static void cleanUp();
    static long count();
    static std::shared_ptr<Bullet> get(long index);
    static void updateAll(float delta);
    static void drawAll(float scale);
};