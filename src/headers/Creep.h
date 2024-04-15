#pragma once
#include <raylib.h>
#include <vector>
#include "PathFinder.h"

class Creep {
protected:
    Vector2 position;
    float angle;
    // WARNING if Path* route is cycling then program will stuck on creep
    std::vector<Vector2> route;
    int index;
    float speed;
public:
    Creep(Vector2 position, Path* route = nullptr, float speed = 2.f);
    void update(float delta);
    void draw(float scale = 20.f); 
    Vector2 getPosition();
    Vector2 getTarget();    
    int getIndex();
    bool isAtEnd();
};