#include <cmath>
#include "IDrawObject.h"

std::list<IDrawObject*> IDrawObject::all;

IDrawObject::IDrawObject() {
    all.push_back(this);
}

void IDrawObject::drawAll(float scale) {
    for (auto li = all.begin(); li != all.end(); li++) 
        (*li)->draw(scale);
}
