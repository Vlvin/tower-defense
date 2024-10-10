#pragma once

#include <Debug.h>
#include <cstdint>

class Node {
public:
  Node(uint8_t layer);
  uint8_t getLayer() const;
  void setLayer(uint8_t layer);
protected:
  uint8_t m_layer;
};