#pragma once

#include <functional>

#include <GameObjects/IGameObject.hpp>

class InputHandler;


class Button : public IGameObject {
public:
  Button(InputHandler& input, Rectangle body, std::function<void(void)> onClick);
  Button(Button&& button, Color color);

  void setColor(Color color);
  Color getColor();


  Rectangle getBody();
// IGameObject
  virtual void update(double deltaTime, CameraObject &camera) override;
  virtual void draw(CameraObject &camera) override;
public:
  InputHandler& input;
protected:
  virtual void onClick();
  virtual bool getMouseCollision();
private:
  Color m_color, m_persistent;
  Rectangle m_body;
  std::function<void(void)> m_onClick;
}; 