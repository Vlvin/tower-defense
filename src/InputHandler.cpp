#include <InputHandler.hpp>
#include <raylib.h>


bool InputHandler::isKeyDown(int key) {
  return IsKeyDown(key);
}

bool InputHandler::isMouseButtonPressed(int key) {
  return IsMouseButtonPressed(key);
}

Vector2 InputHandler::getMousePosition() {
  return GetMousePosition();
}
