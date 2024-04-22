#pragma once
#include <raylib.h>
#include <vector>
#include <cstddef>
#include <memory>
#include "PathFinder.h"
#include "IGameObject.h"

class Creep: public IGameObject {
private:
    static std::vector<std::shared_ptr<Creep>> all;
    static std::shared_ptr<Creep> pop();
protected:
    // WARNING if Path* route is cycling then program will stuck on creep
    std::vector<Vector2> route;
    int index;
    unsigned short hitPoints;
    float speed;
    virtual void hit(short damage);
public:
    Creep(Vector2 position, Path* route = nullptr, float speed = 2.f, unsigned short hitPoints = 8);
    virtual void update(float delta) override;
    static void updateAll(float delta);
    static void drawAll(float scale);
    static void cleanUp();
    static long count();
    static std::shared_ptr<Creep> get(long index);
    Vector2 getTarget();
    int getIndex();
    float getSpeed();
    bool isAtEnd();
    bool isDead();
    static void clearAtEnd();
    friend class Bullet;
};