#pragma once
#include <raylib.h>
#include <list>

class ICollisionBody {
    static std::list<ICollisionBody*> all;
protected:
    Rectangle body;
public:
    ICollisionBody(Rectangle body);
    virtual void onCollision(ICollisionBody* other) = 0;
    virtual std::list<ICollisionBody*> checkCollisions();
};