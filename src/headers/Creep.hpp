#pragma once

#include <IGameObject.hpp>
#include <Map.hpp>

class PathNode;

class Creep : public IGameObject {
public:
  Creep(Rectangle body, std::vector<Vector2> path);
  Creep(Creep creep, Color color);
  
  virtual void update(double deltaTime);
  virtual void draw();
  
  void hit(uint damage);
private:

  Vector2 getPosition();
  
  std::vector<Vector2> m_path;
  uint m_pathIterator;

  uint m_healthPoints;
  float m_directionAngle, m_speed;
  Rectangle m_body;
  
  Color m_color, m_persistent;
  static Texture s_texture;
};