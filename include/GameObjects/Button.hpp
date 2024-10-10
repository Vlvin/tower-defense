#pragma once

#include <functional>

#include <GameObjects/GameObject.hpp>
#include <GameObjects/ICloneable.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <GameObjects/IDrawable.hpp>

class InputHandler;


class Button : public GameObject, public IUpdatable, public IDrawable {
public:
  Button(InputHandler& input, Rectangle body, std::function<void(void)> onClick);
  Button(Button&& button, Color color);

  void setColor(Color color);
  Color getColor();
  Rectangle getBody();


  virtual void update(double deltaTime, CameraObject &camera) override;

  virtual void draw(CameraObject &camera) override;
public:
  InputHandler& input;
protected:
  virtual void onClick();
  virtual bool getMouseCollision(CameraObject& camera);
private:
  Color m_color, m_persistent;
  Rectangle m_body;
  std::function<void(void)> m_onClick;
}; 