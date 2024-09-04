#include <PhysicalInput.hpp>
#include <raylib.h>


bool PhysicalInput::isKeyDown(int key) const {
  return IsKeyDown(key);
}

bool PhysicalInput::isMouseButtonPressed(int key) const {
  return IsMouseButtonPressed(key);
}

Vector2 PhysicalInput::getMousePosition() const {
  return GetMousePosition();
}
