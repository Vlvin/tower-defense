#include <GameObjects/Button.hpp>
#include <InputHandler.hpp>
#include <cmath>
#include <LayerValues.hpp>

Button::Button(InputHandler& input, Rectangle body, std::function<void(void)> onClick) 
  : IGameObject(BUTTON_DRAW_LAYER), input(input)
{
  m_onClick = onClick;
  m_color = m_persistent = WHITE;
  m_body = body;
}

Button::Button(Button&& button, Color color) 
  : Button(button)
{
  m_color = m_persistent = color;
}

void Button::setColor(Color color) {
  m_persistent = color;
} 

Color Button::getColor() {
  return m_color;
}

Rectangle Button::getBody() {
  return m_body;
}

void Button::update(double deltaTime, CameraObject &camera) {
  m_color = m_persistent;
  if (!getMouseCollision(camera)) 
    return;

  // when mouse is in button area
  m_color.r = std::min(std::max(m_persistent.r - 20, 0), 255);
  m_color.g = std::min(std::max(m_persistent.g - 20, 0), 255);
  m_color.b = std::min(std::max(m_persistent.b - 20, 0), 255);
  m_color.a = std::min(std::max(m_persistent.a - 20, 0), 255);

  if (!input.isMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    return;

  // when mouse is in button area and clicking
  m_color.r = std::min(std::max(m_persistent.r - 40, 0), 255);
  m_color.g = std::min(std::max(m_persistent.g - 40, 0), 255);
  m_color.b = std::min(std::max(m_persistent.b - 40, 0), 255);
  m_color.a = std::min(std::max(m_persistent.a - 40, 0), 255);
  onClick();
}

bool Button::getMouseCollision(CameraObject& camera) {
  Vector2 mousePos = input.getMousePosition();
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

void Button::draw(CameraObject &camera) {
  DrawRectangleRec(m_body, m_color);
}

void Button::onClick() {
  m_onClick();
}

