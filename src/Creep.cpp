#include <Creep.hpp>
#include <ColorTools.hpp>
#include <PathNode.hpp>



Texture Creep::s_texture = {
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
  m_speed = {2.5f};
  
  m_path = path;
  for (auto & node : m_path) {
    node.x += 0.5f;
    node.y += 0.5f;
  }
  m_pathIterator = 0;
  m_healthPoints = {1000};
  m_color = m_persistent = WHITE;
  
  
  m_direction = {
    (float)atan2(
      getPosition().y - m_path[m_pathIterator+1].y,
      getPosition().x - m_path[m_pathIterator+1].x
    )
  };
}

Creep::Creep(const Creep &creep, Color color)
  : Creep(creep)
{
  m_color = m_persistent = color;
}

void Creep::hit(uint damage) {
  if (m_healthPoints.value <= damage)
  {
    m_healthPoints.value = 0;
    m_isDead = true;
    return;
  }
  m_healthPoints.value -= damage;
}

void Creep::update(double deltaTime) {
  if (m_healthPoints.value <= 0) 
    m_isDead = true;
  if (m_pathIterator >= m_path.size()) {
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
  
  
  float &direction = m_direction.value;
  float &speed = m_speed.value;

  Vector2 &currentPoint = m_path[m_pathIterator];

  if (CT::vec2Compare(getPosition(), currentPoint, 0.9f)) {
    m_pathIterator++;
  }    
  direction = atan2(
        getPosition().y - currentPoint.y,
        getPosition().x - currentPoint.x
      );

  float distance = CT::vec2Length({
    getPosition().y - currentPoint.y,
    getPosition().x - currentPoint.x
  });

  float stepDistance = CT::vec2Length({
    (float)sin(direction) * speed * (float)deltaTime * 0.001f,
    (float)cos(direction) * speed * (float)deltaTime * 0.001f
  });

  if (distance <= stepDistance) {
    m_body.x = currentPoint.x;
    m_body.y = currentPoint.y;
    
    return;
  }

  // look at how clean it becomes, 
  // no more 
  // cos(m_directionAngle.value) * m_speed.value
  m_body.x -= cos(direction) * speed * deltaTime * 0.001f;
  m_body.y -= sin(direction) * speed * deltaTime * 0.001f;

  /**
   * check colitions and all that stuff
  */

}

void Creep::draw() {

  float scale = 20.f; // rudimentary

  float &direction = m_direction.value;
  float texWidth = s_texture.width;
  float texHeight = s_texture.height;
  DrawTexturePro(
    s_texture, // texture
    {0.f, 0.f, texWidth, texHeight}, // src
    {(m_body.x) * scale, (m_body.y) * scale, m_body.width * scale, m_body.height * scale}, // dest
    {m_body.width * 0.5f * scale, m_body.height * 0.5f * scale}, // origin
    (direction - M_PI*0.5)/M_PI*180, // rotation
    m_color // color
  ); 
  // DrawRectangleRec(
  //   {(m_body.x) * scale, (m_body.y) * scale, m_body.width * scale, m_body.height * scale}, // dest
  //   m_color // color
  // ); 
}

Vector2 Creep::getPosition()
{
  return { m_body.x, m_body.y };
}

OBJECT_OVERRIDE_COMPONENT_CPP(Creep, Body, m_body)
OBJECT_OVERRIDE_COMPONENT_CPP(Creep, Health, m_healthPoints)
OBJECT_OVERRIDE_COMPONENT_CPP(Creep, EnemyTag, m_enemyTag)
OBJECT_OVERRIDE_COMPONENT_CPP(Creep, Direction, m_direction)
OBJECT_OVERRIDE_COMPONENT_CPP(Creep, Speed, m_speed)