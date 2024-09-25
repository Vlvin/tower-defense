#include "Button.hpp"

class InputHandler;

class PlaceHolder : public Button {
public:
  PlaceHolder(InputHandler& input, Vector2 position);
  // virtual void update(double deltaTime, CameraObject &camera) override;
  virtual void draw(CameraObject &camera) override;
  virtual bool getMouseCollision(CameraObject& camera) override;
};