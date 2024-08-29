#pragma once

#include <stdint.h>
#include <LayerValues.hpp>
#include <Debug.h>

class Node {
public:
  Node(uint8_t layer);
  uint8_t getLayer() const;
protected:
  uint8_t m_layer;
};