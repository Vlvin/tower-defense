#pragma once
#include <raylib.h>
#include "PathFinder.h"
#include "ColorTools.h"

class Creep {
protected:
    Vector2 position;
    float angle;
    Path* route;
public:
    Creep(Vector2 position, Path* route = nullptr);
    
};