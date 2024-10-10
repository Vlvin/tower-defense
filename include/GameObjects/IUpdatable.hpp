#pragma once
class CameraObject;

// Interface
class IUpdatable {
public:
  virtual void update(double deltaTime, CameraObject &camera) = 0;
};