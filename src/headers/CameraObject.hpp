#include <raylib.h>
#include <Components.hpp>


class CameraObject {
public:
  CameraObject(float movementSpeed, float scalingSpeed);
  void update(double deltaTime);
  Vector2 &getPosition();
  float &getScale();
protected:
  struct _Camera {
    Vector2 target;
    float zoom;
  } m_camera;
  ::components::Speed m_movementSpeed, m_scalingSpeed;
protected:
  void _handleInput(double deltaTime);
  void _applyRestrictions();
  static constexpr float MIN_ZOOM = 10.f;
  static constexpr float MAX_ZOOM = 40.f;
};