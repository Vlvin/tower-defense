#include "PathFinder.h"
#include "ColorTools.h"
#include "OpenQueue.h"
#include "Map.h"
#include <cstdio>
#include <algorithm>
#include <queue>



std::list<Path*> Path::all = {};

Path::Path(Vector2 position, unsigned int cost, Path* prev) {
    this->cost = cost;
    this->prev = prev;
    this->next = nullptr;
    this->position = position;
    Path::all.push_back(this);

    // printf("new Path on %p\n", this);
}

/**
 * delete all Path objects
 * WARNING: CALL ONLY BEFORE PROGRAM EXIT ONCE
*/
void Path::cleanUp(int signum) {
    for (auto i = Path::all.begin(); i != Path::all.end(); i++) {
        delete (*i);
    }
    while(!Path::all.empty()) Path::all.pop_back();
}

/** 
 *  @param[out] max_depth max depth to check 
 *  @return `true` if on max_depth already passed this point, `false` otherwise
 * */
bool Path::isAlreadyPassed(unsigned int max_depth) {
    Path* i = prev;
    for (int depth = 0; (depth < max_depth) && (i != nullptr); depth++) {
        if (CT::vec2Compare(i->position, this->position)) return true;
        i = i->prev;
    }
    return false;
}

bool Path::isAlreadyPassed(Vector2 pos, unsigned int max_depth) {
    Path* i = prev;
    for (int depth = 0; (depth < max_depth) && (i != nullptr); depth++) {
        if (CT::vec2Compare(i->position, pos)) return true;
        i = i->prev;
    }
    return false;
}


Path *Path::allocator() {
    return this;
}

Vector2 Path::getPosition() {
    return this->position;
}

Path* Path::getNext() {
    return this->next;
}

unsigned int Path::getCost() {
    return this->cost; 
}

unsigned int Path::getFullCost() {
    // int fullCost = 0;
    // Path* i = this;
    // while(i != nullptr) {
    //     fullCost += i->getCost();
    //     i = i->getPrevious();
    // }
    // return fullCost;
    return this->getCost();
}

Path* Path::getPrevious() {
    return this->prev;
}

std::vector<Path*> Path::sortByLength(std::vector<Path*> paths) {
    int index = -1, maxLength = 0, fullCost;
    std::vector<Path*> neopaths;
    while (!paths.empty()) {
        for (int i = 0; i < paths.size(); i++) {
            fullCost = paths[i]->getFullCost();
            if (fullCost > maxLength) {
                maxLength = fullCost;
                index = i;
            }
            neopaths.push_back(paths[i]);
            paths[i] = paths[paths.size() - 1];
            paths.pop_back();
        }
    }
    return neopaths;
}

Path* Path::makeStep(Vector2 position, unsigned int cost, Path* prev) {
    return new Path(position, cost, prev);
}

std::vector<Path*> Path::getNeighbours(Map* map) {
    Vector2 size = map->getSize();
    float x = position.x, y = position.y;
    std::vector<Vector2> neighbourCells = {
        {x + 1, y    },
        {x    , y + 1},
        {x - 1, y    },
        {x    , y - 1}
    };
    std::vector<Path*> neighbours;
    if (position.y <= 0) neighbourCells.pop_back();
    if (position.x <= 0) {
        neighbourCells[2] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.y >= (size.y - 1)) {
        neighbourCells[1] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.x >= (size.x - 1)) {
        neighbourCells[0] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    for (char i = 0; i < neighbourCells.size(); i++) {
        int x = neighbourCells[i].x, y = neighbourCells[i].y;
        neighbours.push_back(makeStep(neighbourCells[i], this->cost+(*map)[y][x].cost, this));
    }
    return neighbours;
}
std::vector<Vector2> Path::getNeighboursPositions(Map* map) {
    Vector2 size = map->getSize();
    float x = position.x, y = position.y;
    std::vector<Vector2> neighbourCells = {
        {x + 1, y    },
        {x    , y + 1},
        {x - 1, y    },
        {x    , y - 1}
    };
    if (position.y <= 0) neighbourCells.pop_back();
    if (position.x <= 0) {
        neighbourCells[2] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.y >= (size.y - 1)) {
        neighbourCells[1] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.x >= (size.x - 1)) {
        neighbourCells[0] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    return neighbourCells;
}

unsigned int Path::manhattenDistance(Vector2 position) {
    return abs(position.x - (this->position.x)) + abs(position.y - (this->position.y));
}

Path* Path::findPath(Map *map, MapUnit goal) {
    auto cmp = [&] (Path* a, Path* b) {
                    return (
                        ((a->manhattenDistance(goal.position))+(a->getFullCost())) 
                      > ((b->manhattenDistance(goal.position))+(b->getFullCost())));
                };
    std::priority_queue<Path*, std::vector<Path*>, decltype(cmp)> mainPaths(cmp);

    std::vector<Vector2> tempPaths;

    int width = map->getSize().x, height = map->getSize().y;
    int locX, locY;
    typedef struct shortunit {
        unsigned int cost;
        Path* point;
    } shortunit;

    shortunit costMap[width*height];

    for (int i = 0; i < width*height; i++) costMap[i] = { uint32_t(-1), nullptr};

    Path* currentPath = this;
    unsigned int actual_size;
    while(!CT::vec2Compare(currentPath->getPosition(), goal.position)) {
        // printf("%f:%f\n", currentPath->position.x, currentPath->position.y);
        tempPaths = currentPath->getNeighboursPositions(map);

        actual_size = mainPaths.size();
        for (int i = 0; i < tempPaths.size(); i++) {
            Vector2 pos = tempPaths[i];
            unsigned int cellCost = currentPath->cost + (*map)[int(pos.y)][int(pos.x)].cost;
            if ((!currentPath->isAlreadyPassed(pos, 5)) && (costMap[int(pos.y)*width+int(pos.x)].cost > cellCost)) {   
                costMap[int(pos.y)*width+int(pos.x)] = {cellCost, makeStep(pos, cellCost, currentPath)};
                mainPaths.push(costMap[int(pos.y)*width+int(pos.x)].point);
                // printf("%u::%f %f\n", currentPath->cost + cellCost, pos.x, pos.y);
            }
        }
        // if (mainPaths.size() <= actual_size) mainPaths.pop();
        currentPath = mainPaths.top();
        mainPaths.pop(); 
        locX = currentPath->getPosition().x, locY = currentPath->getPosition().y;
        if (costMap[locY*width+locX].cost <= currentPath->getFullCost()) currentPath = costMap[locY*width+locX].point;
    }   
    return currentPath;

}

Path* Path::_findPathVisual(Map *map, MapUnit goal) {
    auto cmp = [&] (Path* a, Path* b) {
                    return (
                        ((a->manhattenDistance(goal.position))+(a->getFullCost())) 
                      > ((b->manhattenDistance(goal.position))+(b->getFullCost())));
                };
    std::priority_queue<Path*, std::vector<Path*>, decltype(cmp)> mainPaths(cmp);

    std::vector<Vector2> tempPaths;

    int width = map->getSize().x, height = map->getSize().y;
    int locX, locY;
    typedef struct shortunit {
        unsigned int cost;
        Path* point;
    } shortunit;

    shortunit costMap[width*height];

    for (int i = 0; i < width*height; i++) costMap[i] = { uint32_t(-1), nullptr};

    Path* currentPath = this;
    unsigned int actual_size;
    while(!CT::vec2Compare(currentPath->getPosition(), goal.position)) {

        tempPaths = currentPath->getNeighboursPositions(map);
        actual_size = mainPaths.size();

        for (int i = 0; i < tempPaths.size(); i++) {
            Vector2 pos = tempPaths[i];
            unsigned int cellCost = currentPath->cost + (*map)[int(pos.y)][int(pos.x)].cost;
            if ((!currentPath->isAlreadyPassed(pos, 5)) && (costMap[int(pos.y)*width+int(pos.x)].cost > cellCost)) {   
                costMap[int(pos.y)*width+int(pos.x)] = {cellCost, makeStep(pos, cellCost, currentPath)};
                mainPaths.push(costMap[int(pos.y)*width+int(pos.x)].point);
            }
        }

        currentPath = mainPaths.top();
        mainPaths.pop(); 

        // important moment: if cost of top path is more/equals than shortest from map then we using shortest from map and loosing actual 
        locX = currentPath->getPosition().x, locY = currentPath->getPosition().y;
        if (costMap[locY*width+locX].cost <= currentPath->getFullCost()) 
            currentPath = costMap[locY*width+locX].point;

        // Clear back; Draw map; Draw path;
        BeginDrawing();
            ClearBackground(BLACK);
            map->draw(20.f);
            currentPath->drawReverse(20.f);
        EndDrawing();
    }   
    return currentPath;
}

void Path::drawReverse(float scale) {
    Path *i = this;
    while(i != nullptr) {
        DrawRectangle(i->getPosition().x*scale, i->getPosition().y*scale, scale, scale, PINK);
        i = i->getPrevious();
    }
}

Path* Path::setRouteFromStart() {
    Path *i = this;
    while (i->prev != nullptr) {
        i->prev->next = i; // in i-1 setting up pointer to i
        i = i->prev; // setting i to i-1
    }
    return i;
}

Path* Path::findPathAndBuild(Map* map, MapUnit goal) {
    return (this->findPath(map, goal))->setRouteFromStart();
}