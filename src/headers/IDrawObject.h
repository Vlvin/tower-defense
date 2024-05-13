#pragma once
#include <raylib.h>
#include <list>

class IDrawObject {
    static std::list<IDrawObject*> all;
public:
    IDrawObject();
    virtual void draw(float scale) = 0;
    static void drawAll(float scale);
};