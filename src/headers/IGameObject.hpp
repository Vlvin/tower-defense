#pragma once

#include <iostream>

#include <raylib.h>

class IGameObject {
public:
  virtual void update(double deltaTime) = 0;
  virtual void draw() = 0;
};