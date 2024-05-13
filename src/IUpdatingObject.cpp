#include "IUpdatingObject.h"


std::list<IUpdatingObject*> IUpdatingObject::all;

IUpdatingObject::IUpdatingObject() {
    all.push_back(this);
}

void IUpdatingObject::updateAll(float deltaTime) {
    for (auto li = all.begin(); li != all.end(); li++) 
        (*li)->update(deltaTime);
}