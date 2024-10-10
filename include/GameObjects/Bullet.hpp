#pragma once
#include <GameObjects/GameObject.hpp>
#include <GameObjects/ICloneable.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <GameObjects/IDrawable.hpp>

class Bullet : public GameObject, public IUpdatable, public IDrawable, public ICloneable {
public:
  Bullet(Rectangle body, float direction);
  Bullet(Bullet&& bullet, Color color);

  virtual void update(double deltaTime, CameraObject &camera) override;

  virtual void draw(CameraObject &camera) override;
  
  virtual std::shared_ptr<ICloneable> clone() override;
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