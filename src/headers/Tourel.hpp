#pragma once
#include <IGameObject.hpp>
#include <Creep.hpp>
#include <Bullet.hpp>

class Tourel : public IGameObject {
public:
  Tourel(Rectangle body, float rangeOfAction, Bullet bullet);
  Tourel(const Tourel &tourel, Color color);
  virtual void update(double deltaTime) override;
  virtual void draw() override;
protected:
  void shoot();
  void locateTarget();
  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
protected:
  float m_rangeOfAction, m_directionAngle;
  std::shared_ptr<IGameObject> m_target;

  components::Body m_body;

  
  Bullet m_bullet;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};