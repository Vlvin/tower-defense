#pragma once
#include <IGameObject.hpp>

class Bullet : public IGameObject {
public:
  Bullet(Rectangle body, float direction);
  Bullet(Bullet bullet, Color color);
  virtual void update(double deltaTime) override;
  virtual void draw() override;

protected:
  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Direction)
  OBJECT_OVERRIDE_COMPONENT_H(Speed)

protected:
  Color m_color, m_persistens;
  components::Body m_body;
  components::Direction m_direction;
  components::Speed m_speed;

  static Texture s_texture;

};