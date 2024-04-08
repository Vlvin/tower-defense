#include "PathFinder.h"
#include "ColorTools.h"
#include "Map.h"
#include <cstdio>

std::vector<Path*> Path::all = {};

Path::Path(Vector2 position, int cost, Path* prev) {
    this->cost = cost;
    this->prev = prev;
    this->position = position;
    Path::all.push_back(this);
    printf("new Path on %p\n", this);
}

/**
 * delete all Path objects
 * WARNING: CALL ONLY BEFORE PROGRAM EXIT ONCE
*/
void Path::cleanUp() {
    for (int i = 0; i < Path::all.size(); i++) {
        delete (Path::all.at(Path::all.size() - 1));
        Path::all.pop_back();
    }
}

/** 
 *  @param[out] max_depth max depth to check 
 *  @return `true` if on max_depth already passed this point, `false` otherwise
 * */
bool Path::isAlreadyPassed(unsigned int max_depth) {
    Path* i = prev;
    for (int depth = 0; (depth < max_depth) && (i != nullptr); ++depth) {
        if (CT::vec2Compare(i->position, this->position)) return true;
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

int Path::getSize() {
    return this->cost;
}

Path* Path::getPrevious() {
    return this->prev;
}

std::vector<Path*> Path::getNeighbours(Map* map) {
    Vector2 size = map->getSize();
    std::vector<Vector2> neighbourCells = {
        {position.x + 1, position.y},
        {position.x, position.y + 1},
        {position.x - 1, position.y},
        {position.x, position.y - 1}
    };
    std::vector<Path*> neighbours;
    if (position.y <= 0) neighbourCells.pop_back();
    if (position.x <= 0) {
        neighbourCells[2] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.y >= (size.x - 1)) {
        neighbourCells[1] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (position.x >= (size.x - 1)) {
        neighbourCells[0] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    for (char i = 0; i < neighbourCells.size(); i++) {
        int x = neighbourCells[i].x, y = neighbourCells[i].y;
        neighbours.push_back(new Path(neighbourCells[i], (*map)[y][x].cost, this));
    }
    return neighbours;
}


Path* Path::findPath(Map *map, MapUnit goal) {
    
}