#pragma once
#include <raylib.h>
#include <vector>
#include <random>

typedef struct MapUnit {
    Color color;
    Vector2 position;
    unsigned int cost;
} MapUnit;

typedef enum Tile {
    GRASS,
    ROAD,
    TOUREL,
    START,
    FINISH
} Tile_t;

class Map {
protected:
    int width, height;
    MapUnit *data;
    std::vector<MapUnit> spawns;
    std::vector<MapUnit> goals;
    std::vector<MapUnit> placeholders;
    Map(int width, int height, Color* data);
public:
    ~Map();
    static Map loadFromFile(const char* filename);
    MapUnit* operator[] (int index);
    MapUnit getAny(Tile_t type);
    void draw(float scale);
    Vector2 getSize();
};