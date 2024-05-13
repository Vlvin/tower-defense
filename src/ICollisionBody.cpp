#include "ICollisionBody.h"

std::list<ICollisionBody*> ICollisionBody::all;

ICollisionBody::ICollisionBody(Rectangle body) {
    this->body = body;
    all.push_back(this);
}

std::list<ICollisionBody*> ICollisionBody::checkCollisions() {
    std::list<ICollisionBody*> temp;
    for (auto li = all.begin(); li != all.end(); li++) {
        Rectangle other = (*li)->body;
        if (
                (body.x < (other.x + other.width))
             && (other.x < (body.x + body.width))
             && (body.y < (other.y + other.height))
             && (other.y < (body.y + body.height))) 
        {
            temp.push_back(*li);
        }
    }
    return temp;
}
