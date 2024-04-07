#pragma once
#include <raylib.h>

class Map {
protected:
    int width, height;
public:
    Color *data;
    static Map load(const char* filename);
    Map(int width, int height, Color* data);
    ~Map();
    Color* operator[] (int index);
    Vector2 getSize();
};