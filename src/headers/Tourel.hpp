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
  inline void shoot();
  inline void predictTargetPosition();
  void locateTarget();
  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Direction)
protected:
  float m_rangeOfAction;
#ifdef NDEBUG
  float predX, predY;
#endif
  std::shared_ptr<IGameObject> m_target;

  components::Body m_body;
  components::Direction m_directionAngle;

  
  Bullet m_bullet;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};