#pragma once
#include <raylib.h>
#include <vector>
#include <cstddef>
#include <memory>
#include "PathFinder.h"
#include "IGameObject.h"

class Creep: public IGameObject {
private:
    static Texture2D texture_;
protected:
    // WARNING if Path* route is cycling then program will stuck on creep
    std::vector<Vector2> route;
    int index;
    unsigned short hitPoints;
    float speed;
    virtual void hit(short damage);
public:
    Creep(Vector2 position, Path* route = nullptr, float speed = 2.f, unsigned short hitPoints = 8, const char* texture_path = NULL);
    virtual void update(float delta) override;
    // virtual void draw(float scale) override;
    static void cleanUp();
    Vector2 getTarget();
    int getIndex();
    float getSpeed();
    bool isAtEnd();
    bool isCollidable();
    bool isDead();
    friend class Bullet;
};