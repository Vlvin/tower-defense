#pragma once

#include <GameObjects/IGameObject.hpp>
#include <GameObjects/Map.hpp>

class PathNode;


class Creep : public IGameObject {
public:
  Creep(Rectangle body, std::vector<Vector2> path);
  Creep(Creep&& creep, Color color);
  
  virtual void update(double deltaTime, CameraObject &camera) override;
  virtual void draw(CameraObject &camera) override;
  
  void hit(uint damage);
protected:

  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Direction)
  OBJECT_OVERRIDE_COMPONENT_H(Speed)
  OBJECT_OVERRIDE_COMPONENT_H(Health)
  OBJECT_OVERRIDE_COMPONENT_H(EnemyTag)
  
  std::vector<Vector2> m_path;
  uint m_pathIterator;

  components::Health m_healthPoints;
  components::Body m_body;
  components::EnemyTag m_enemyTag;
  components::Direction m_direction;
  components::Speed m_speed;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};