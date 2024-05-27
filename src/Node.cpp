#include "Node.h"
#include "Scene.h"

Node::Node(Scene& parent, uint32_t layer)
: parent(parent), layer(layer) {}

bool Node::isUpdatable() {
    return false;
}

uint32_t Node::getDrawLayer() {
    return layer;
}

void Node::setDrawLayer(uint32_t layer) {
    this->layer = layer;
}