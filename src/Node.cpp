#include <Node.hpp>

Node::Node(uint8_t layer) {
  m_layer = layer;
}

uint8_t Node::getLayer() const {
  return m_layer;
}