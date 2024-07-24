#include <Creep.hpp>
#include <ColorTools.hpp>
#include <PathNode.hpp>



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
  m_speed = 2.5f;
  
  m_path = path;
  m_pathIterator = 0;
  m_healthPoints = 10;
  m_color = m_persistent = WHITE;
  
  
  m_directionAngle = atan2
    (
      getPosition().y - m_path[m_pathIterator+1].y,
      getPosition().x - m_path[m_pathIterator+1].x
    );
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
  // std::cout << deltaTime << '\n';
  m_directionAngle =
    atan2
    (
      getPosition().y - m_path[m_pathIterator].y,
      getPosition().x - m_path[m_pathIterator].x
    );


  m_body.x -= cos(m_directionAngle) * m_speed * deltaTime * 0.001f;
  m_body.y -= sin(m_directionAngle) * m_speed * deltaTime * 0.001f;

  /**
   * check colitions and all that stuff
  */



}

void Creep::draw() {

  float scale = 10.f; // rudimentary
  DrawTexturePro
  (
    s_texture, // texture
    {0.f, 0.f, (float)s_texture.width, (float)s_texture.height}, // src
    {(m_body.x + 0.5f) * scale, (m_body.y + 0.5f) * scale, m_body.width, m_body.height}, // dest
    {m_body.width * 0.5f, m_body.height * 0.5f}, // origin
    (m_directionAngle - M_PI*0.5)/M_PI*180, // rotation
    m_color // color
    ); 
}

Vector2 Creep::getPosition()
{
  return {m_body.x, m_body.y};
}