#pragma once

#include <GameObjects/Map.hpp>
#include <GameObjects/GameObject.hpp>
#include <GameObjects/ICloneable.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <GameObjects/IDrawable.hpp>

class PathNode;


class Creep : public GameObject, public IUpdatable, public IDrawable, public ICloneable {
public:
  Creep(Rectangle body, Map& map, std::vector<Vector2> path);
  Creep(Rectangle body, Map& map, MapUnit goal);
  Creep(Creep&& creep, Color color);
  
  virtual void update(double deltaTime, CameraObject &camera) override;

  virtual void draw(CameraObject &camera) override;

  virtual std::shared_ptr<ICloneable> clone() override;

  void setPath(Vector2 goalPos);
  void hit(uint damage);
protected:

  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Money)
  OBJECT_OVERRIDE_COMPONENT_H(Direction)
  OBJECT_OVERRIDE_COMPONENT_H(Speed)
  OBJECT_OVERRIDE_COMPONENT_H(Health)
  OBJECT_OVERRIDE_COMPONENT_H(EnemyTag)
  
  std::vector<Vector2> m_path;
  uint m_pathIterator;
  Map& m_map;

  components::Health m_healthPoints;
  components::Body m_body;
  components::Money m_money;
  components::EnemyTag m_enemyTag;
  components::Direction m_direction;
  components::Speed m_speed;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};