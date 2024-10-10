#pragma once
class CameraObject;

class IDrawable {
public:
  virtual void draw(CameraObject &camera) = 0;
};