#pragma once
#include <raylib.h>
#include <vector>

class Map;
class MapUnit;

class Path {
protected:
    static std::vector<Path*> all;
    Path* prev;
    int cost;
    Vector2 position;
public:
    Path(Vector2 position, int cost, Path* prev = nullptr);
    int getSize();
    bool isAlreadyPassed(unsigned int max_depth);
    Path* getPrevious();
    Vector2 getPosition();
    Path* allocator();
    std::vector<Path*> getNeighbours(Map* map);
    Path* findPath(Map* map, MapUnit goal);
    static void cleanUp();
};
