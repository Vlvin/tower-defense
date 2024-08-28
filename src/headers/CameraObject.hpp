#include <raylib.h>
#include <Components.hpp>

class CameraObject {
public:
  CameraObject(float movementSpeed, float scalingSpeed);
  void update(double deltaTime);
  Vector2 &getPosition();
  float &getScale();
protected:
  Camera2D m_camera;
  ::components::Speed m_movementSpeed, m_scalingSpeed;
protected:
  void _handleInput(double deltaTime);
  void _applyRestrictions();
};