#pragma once

#include <iostream>
#include <random>

#include <raylib.h>
#include <Node.hpp>

class IGameObject {
public:
  inline IGameObject(uint8_t layer) 
    : m_node(layer), m_isDead(false)
  {}

  bool isDead() { return m_isDead; }
  uint8_t getLayer() { return m_node.getLayer(); }

  virtual void update(double deltaTime) = 0;
  virtual void draw() = 0;
protected:
  Node m_node;
  bool m_isDead;
};