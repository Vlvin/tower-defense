#pragma once

#include <functional>

#include "IGameObject.hpp"




class Button : public IGameObject {
public:
  Button(Rectangle body, std::function<void(void)> onClick);
  Button(Rectangle body, std::function<void(void)> onClick, Color color);

  void setColor(Color color);
// IGameObject
  virtual void update(double deltaTime) override;
  virtual void draw() override;
protected:
  virtual void onClick();
  virtual bool getMouseCollision();
private:
  Color m_color, m_persistent;
  Rectangle m_body;
  std::function<void(void)> m_onClick;
}; 