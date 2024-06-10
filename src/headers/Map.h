#pragma once
#include <raylib.h>
#include <vector>
#include <random>
#include "Scene.h"
#include "Node.h"


typedef enum Tile {
    GRASS,
    ROAD,
    TOUREL,
    START,
    FINISH
} Tile_t;

typedef struct MapUnit {
    Color color;
    Vector2 position;
    unsigned int cost;
    Tile_t type;
} MapUnit;

class Map : public Node {
protected:
    int width, height;
    double lastSpawned;
    MapUnit *data;
    std::vector<MapUnit> spawns;
    std::vector<MapUnit> goals;
    std::vector<MapUnit> placeholders;
    Map(Scene& parent, int width, int height, Color* data);
public:
    ~Map();
    static Map loadFromFile(Scene& parent, const char* filename);
    MapUnit* operator[] (int index);
    MapUnit getAny(Tile_t type);
    virtual void update(float deltaTime) override;
    virtual void draw(float scale, Vector2 camera) override;
    Vector2 getSize();
    void clear();
};