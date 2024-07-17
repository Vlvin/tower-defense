#pragma once

#include <iostream>
#include <random>

#include <raylib.h>
#include "Node.hpp"

class IGameObject {
public:
  inline IGameObject(uint8_t layer) 
    : node(layer), m_isDead(false)
  {}
  bool isDead() { return m_isDead; }
  virtual void update(double deltaTime) = 0;
  virtual void draw() = 0;
public:
  const Node node;
protected:
  bool m_isDead;
};