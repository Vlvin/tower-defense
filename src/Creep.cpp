#include "Creep.hpp"
#include "ColorTools.hpp"
#include "PathNode.hpp"



Texture Creep::s_texture
{
  0,
  0,
  0,
  0,
  0
};

Creep::Creep(Rectangle body, std::vector<Vector2> path)
  : IGameObject(CREEP_DRAW_LAYER)
{
  if (!s_texture.width) {
    auto image = LoadImage("assets/Zombie.png");
    s_texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }
  m_body = body;
  m_speed = 5.f;
  
  m_path = path;
  m_pathIterator = 0;
  m_healthPoints = 10;
  m_color = m_persistent = WHITE;
}

Creep::Creep(Creep creep, Color color)
  : Creep(creep)
{
  m_color = m_persistent = color;
}

void Creep::hit(uint damage) {
  if (m_healthPoints <= damage)
  {
    m_healthPoints = 0;
    m_isDead = true;
    return;
  }
  m_healthPoints -= damage;
}

void Creep::update(double deltaTime) {
  if (m_healthPoints <= 0) m_isDead = true;
  if (m_pathIterator >= m_path.size())
  {
    /**
     * Hit the player
     * if once then 
     * m_isDead = true;
     * else 
     * ! m_isDead = true;
     * 
     * but since we have no player yet
    */


    m_isDead = true;
  }
  if (m_isDead) return;

  if (CT::vec2Compare(getPosition(), m_path[m_pathIterator]))
    m_pathIterator++;

  m_directionAngle = 
    atan2
    (
      getPosition().y - m_path[m_pathIterator].y,
      getPosition().x - m_path[m_pathIterator].x
    );

  m_body.x += cos(m_directionAngle+(M_PI*0.5)) * m_speed * deltaTime;
  m_body.y -= sin(m_directionAngle+(M_PI*0.5)) * m_speed * deltaTime;

  /**
   * check colitions and all that stuff
  */



}

void Creep::draw() {
  DrawTexturePro
  (
    s_texture, // texture
    {0.f, 0.f, (float)s_texture.width, (float)s_texture.height}, // src
    m_body, // dest
    {0.5f, 0.5f}, // origin
    m_directionAngle/M_PI*180, // rotation
    m_color // color
    ); 
}

Vector2 Creep::getPosition()
{
  return {m_body.x, m_body.y};
}