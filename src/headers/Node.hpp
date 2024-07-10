#pragma once

#include "stdint.h"
#include "LayerValues.hpp"

class Node {
public:
  Node(uint8_t layer);
  uint8_t getLayer();
private:
  uint8_t m_layer;
};