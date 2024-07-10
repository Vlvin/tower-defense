#pragma once

#include <iostream>
#include <random>

#include <raylib.h>
#include "Node.hpp"

class IGameObject : public Node {
public:
  inline IGameObject(uint8_t layer) 
    : Node(layer)
  {}
  virtual void update(double deltaTime) = 0;
  virtual void draw() = 0;
};