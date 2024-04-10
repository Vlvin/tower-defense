#pragma once
#include <raylib.h>
#include <vector>
#include <list>

class Map;
class MapUnit;

/** Path class represents path unit with link to next and previous 
 * When you create Path node by hands your node has no next and even prev (it will never have prev)
 * but if you will call Path::findPath(&map, MapUnit goal) it will build path to goal and all nodes except this will have prev
 * next you need to take last node from findPath and call it's setRouteFromStart
*/
class Path {
protected:
    static std::list<Path*> all;
    Path* prev;
    Path* next;
    int cost;
    Vector2 position;
public:
    Path(Vector2 position, int cost, Path* prev = nullptr);

    Path* getPrevious();
    Path* getNext();
    Vector2 getPosition();
    int getCost();
    int getFullCost();

    int manhattenDistance(Vector2 position);

    bool isAlreadyPassed(unsigned int max_depth);

    Path* allocator();
    Path* findPath(Map* map, MapUnit goal);

    std::vector<Path*> getNeighbours(Map* map);

    static std::vector<Path*> sortByLength(std::vector<Path*> paths);
    static void cleanUp();

    Path* setRouteFromStart();
    // for clean writing
    Path* findPathAndBuild(Map* map, MapUnit goal);
};
