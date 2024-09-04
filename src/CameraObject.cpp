#include <CameraObject.hpp>
#include <cmath>
#include <Debug.h>

#include <InputHandler.hpp>


void CameraObject::update(double deltaTime) {
  _handleInput(deltaTime);
  _applyRestrictions();
}

void CameraObject::_handleInput(double deltaTime) {
  if (input.isKeyDown(KEY_W)){
    m_camera.target.y -= m_movementSpeed.value * deltaTime;
  }
  if (input.isKeyDown(KEY_S)){
    m_camera.target.y += m_movementSpeed.value * deltaTime;
  }
  if (input.isKeyDown(KEY_A)){
    m_camera.target.x -= m_movementSpeed.value * deltaTime;
  }
  if (input.isKeyDown(KEY_D)){
    m_camera.target.x += m_movementSpeed.value * deltaTime;
  }
  
  if (input.isKeyDown(KEY_C))
    m_camera.zoom += m_movementSpeed.value * deltaTime;
  if (input.isKeyDown(KEY_F))
    m_camera.zoom -= m_movementSpeed.value * deltaTime;
}


void CameraObject::_applyRestrictions() {
  m_camera.zoom = std::max(MIN_ZOOM, std::min(m_camera.zoom, MAX_ZOOM));
}

CameraObject::CameraObject(InputHandler& input, float movementSpeed, float scalingSpeed) 
 : input(input)
{
  m_camera.target = {2.f, 2.f};
  m_camera.zoom = 10.f;
  m_movementSpeed = { movementSpeed };
  m_scalingSpeed = { scalingSpeed };
}

Vector2 &CameraObject::getPosition() {
  return m_camera.target;
}

float &CameraObject::getScale() {
  return m_camera.zoom;
}


