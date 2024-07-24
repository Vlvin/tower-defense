#pragma once

#include <IGameObject.hpp>
#include <Map.hpp>

class PathNode;


class Creep : public IGameObject {
public:
  Creep(Rectangle body, std::vector<Vector2> path);
  Creep(const Creep &creep, Color color);
  
  virtual void update(double deltaTime);
  virtual void draw();
  
  void hit(uint damage);
private:

  Vector2 getPosition();

  OBJECT_OVERRIDE_COMPONENT_H(Body)
  OBJECT_OVERRIDE_COMPONENT_H(Health)
  OBJECT_OVERRIDE_COMPONENT_H(EnemyTag)
  
  std::vector<Vector2> m_path;
  uint m_pathIterator;

  components::Health m_healthPoints;
  components::Body m_body;
  components::EnemyTag m_enemyTag;
  
  
  float m_directionAngle, m_speed;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};