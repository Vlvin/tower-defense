#include "Node.h"
#include "Scene.h"

Node::Node(Scene& parent)
: parent(parent) {}

bool Node::isUpdatable() {
    return false;
}