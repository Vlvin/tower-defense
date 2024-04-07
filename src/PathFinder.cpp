#include "PathFinder.h"


Path::Path(int cost, Path* prev) {
    this->cost = cost;
    this->prev = prev;
}

/** 
 *  @param[out] max_depth max depth to check 
 *  @return `true` if on max_depth already passed this point, `false` otherwise
 * */
bool Path::isAlreadyPassed(unsigned int max_depth) {
    Path* i = prev;
    for (int depth = 0; (depth > max_depth) && (i != nullptr); ++depth) {
        if (i == this) return true;
        i = i->prev;
    }
    return false;
}

int Path::getSize() {
    return this->cost;
}

Path *Path::allocator() {
    return this;
}