#pragma once

/**
 * This Class is used only for dependency injection, so I could test results with fake input
*/

struct Vector2;

class InputHandler {
public:
  bool isKeyDown(int key);
  bool isMouseButtonPressed(int key);
  Vector2 getMousePosition();
};