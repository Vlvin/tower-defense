#include "Button.hpp"


Button::Button(Rectangle body, std::function<void(void)> onClick) 
  : IGameObject(BUTTON_DRAW_LAYER)
{
  m_onClick = onClick;
  m_color = m_persistent = WHITE;
  m_body = body;
}

Button::Button(Button button, Color color) 
  : Button(button)
{
  m_color = m_persistent = color;
}

void Button::setColor(Color color) {
  m_persistent = color;
} 

// IGameObject
void Button::update(double deltaTime) {
  m_color = m_persistent;
  if (!getMouseCollision()) return;

  // when mouse is in button area
  m_color.r = m_persistent.r - 20;
  m_color.g = m_persistent.g - 20;
  m_color.b = m_persistent.b - 20;
  m_color.a = m_persistent.a - 20;

  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

  // when mouse is in button area and clicking
  onClick();

}

bool Button::getMouseCollision() {
  Vector2 mousePos = GetMousePosition();
  return (
    (
      mousePos.x > (m_body.x) && 
      mousePos.x < (m_body.x + m_body.width)
    ) 
    &&
    (
      mousePos.y > (m_body.y) && 
      mousePos.y < (m_body.y + m_body.height)
    )
  );
}

void Button::draw() {
  DrawRectangleRec(m_body, m_color);
}

// private

void Button::onClick() {
  m_onClick();
}

