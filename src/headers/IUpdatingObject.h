#pragma once
#include <raylib.h>
#include <list>

class IUpdatingObject {
    static std::list<IUpdatingObject*> all;
public:
    IUpdatingObject();
    virtual void update(float deltaTime) = 0;
    static void updateAll(float deltaTime);
};