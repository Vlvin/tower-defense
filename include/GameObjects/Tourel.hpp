#pragma once
#include <GameObjects/GameObject.hpp>
#include <GameObjects/ICloneable.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <GameObjects/IDrawable.hpp>
#include <GameObjects/Creep.hpp>
#include <GameObjects/Bullet.hpp>


class Tourel : public GameObject, public IUpdatable, public IDrawable, public ICloneable {
public:
  Tourel(Rectangle body, float rangeOfAction, Bullet bullet);
  Tourel(const Tourel &tourel, Color color);

  virtual void update(double deltaTime, CameraObject& camera) override;

  virtual void draw(CameraObject& camera) override;

  virtual std::shared_ptr<ICloneable> clone() override;
protected:
  inline void shoot();
  inline void predictTargetPosition();
  void locateTarget();
  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Direction)
protected:
  float m_shootFreq, m_lastShot;
  float m_rangeOfAction;
#ifdef NDEBUG
  float predX, predY;
#endif
  std::shared_ptr<GameObject> m_target;

  components::Body m_body;
  components::Direction m_directionAngle;

  
  Bullet m_bullet;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};