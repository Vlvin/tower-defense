#include "PathFinder.h"
#include "ColorTools.h"
#include "Map.h"
#include <cstdio>
#include <algorithm>

std::list<Path*> Path::all = {};

Path::Path(Vector2 position, int cost, Path* prev) {
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
void Path::cleanUp() {
    for (auto i = Path::all.begin(); i != Path::all.end(); i++) {
        delete (*i);
    }
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


Path *Path::allocator() {
    return this;
}

Vector2 Path::getPosition() {
    return this->position;
}

Path* Path::getNext() {
    return this->next;
}

int Path::getCost() {
    return this->cost; 
}

int Path::getFullCost() {
    int fullCost = 0;
    Path* i = this;
    while(i != nullptr) {
        fullCost += i->getCost();
        i = i->getPrevious();
    }
    return fullCost;
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

int Path::manhattenDistance(Vector2 position) {
    return abs(position.x - this->position.x) + abs(position.x - this->position.x);
}

Path* Path::findPath(Map *map, MapUnit goal) {
    std::list<Path*> mainPaths;
    std::vector<Path*> tempPaths;
    Path* currentPath = this;
    while(!CT::vec2Compare(currentPath->getPosition(), goal.position)) {
        tempPaths = currentPath->getNeighbours(map);
        for (int i = 0; i < tempPaths.size(); i++)
            // if (!tempPaths[i]->isAlreadyPassed(10))
            {
                    printf("b4 %d\n", mainPaths.size());
                    mainPaths.remove_if(
                            [&] (Path *current) { 
                                return (
                                    (current->getFullCost() >= tempPaths[i]->getFullCost()) && 
                                    ( CT::vec2Compare(current->getPosition(), tempPaths[i]->getPosition()) )
                                ); }
                        );
                    printf("after %d\n", mainPaths.size());
                    mainPaths.push_back(tempPaths[i]);
            }
        
        mainPaths.sort(
            [=] (Path* a, Path* b) {
                if (a == nullptr) return false;
                if (b == nullptr) return true;
                return 
                // (a->getFullCost() > b->getFullCost()) &&
                        ((a->manhattenDistance(goal.position)+a->getFullCost()) > (b->manhattenDistance(goal.position)+b->getFullCost()));
            }
        );
        mainPaths.remove_if(
                [] (Path *current) { return current->isAlreadyPassed(5); }
        );
        currentPath = mainPaths.back();
        mainPaths.pop_back();
    }   
    return currentPath;

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