#pragma once

/**
 * This Class is used only for dependency injection, so I could test results with fake input
*/

struct Vector2;

class InputHandler {
public:
  virtual bool isKeyDown(int key) const = 0;
  virtual bool isMouseButtonPressed(int key) const = 0;
  virtual Vector2 getMousePosition() const = 0;
};