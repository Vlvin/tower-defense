#include <InputHandler.hpp>

class PhysicalInput : public InputHandler { 
public:
  bool isKeyDown(int key) const override;
  bool isMouseButtonPressed(int key) const override;
  Vector2 getMousePosition() const override;
};