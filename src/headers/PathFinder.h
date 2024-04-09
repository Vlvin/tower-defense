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
    int getCost();
    int getFullCost();
    bool isAlreadyPassed(unsigned int max_depth);
    Path* getPrevious();
    Vector2 getPosition();
    int manhattenDistance(Vector2 position);
    Path* allocator();
    std::vector<Path*> getNeighbours(Map* map);
    Path* findPath(Map* map, MapUnit goal);
    static std::vector<Path*> sortByLength(std::vector<Path*> paths);
    static void cleanUp();
};
