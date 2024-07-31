#include <Bullet.hpp>
#include <SceneManager.hpp>
#include <ColorTools.hpp>
#include <Creep.hpp>

Texture Bullet::s_texture = {
  0,
  0,
  0,
  0,
  0
};

Bullet::Bullet(Rectangle body, float direction) 
  : IGameObject(BULLET_DRAW_LAYER) 
{  
  if (!s_texture.width) {
    auto image = LoadImage("assets/Tourel.png");
    s_texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }
  m_direction = {direction};
  m_body = body;
  m_speed = { 5.f };
  m_color = m_persistens = WHITE;
}


Bullet::Bullet(Bullet bullet, Color color) 
  : Bullet(bullet)
{
  m_color = m_persistens = color;
}


void Bullet::update(double deltaTime) {
  if (isDead()) 
    return;
  
  float &direction = m_direction.value;
  float &speed = m_speed.value;

  // update position
  m_body.x -= cos(direction) * speed * deltaTime * 0.001f;
  m_body.y -= sin(direction) * speed * deltaTime * 0.001f;



  // check collision
  auto &parent = SceneManager::Back();
  auto &bullet = m_body;
  for (auto &object : parent) {
    bool colliding = false;
    object->dispatch([&] (components::EnemyTag&, components::Body& body) {
      DLOG("Enemy");
      if (CT::boxCollision(body, bullet, 1.f)) {
        colliding = true;
        DLOG("Collision");
      }
    });
    if (colliding) {
      std::dynamic_pointer_cast<Creep>(object)->hit(1); // damage
      DLOG("Hit");
      this->m_isDead = true;
      break;
    }
  }


}

void Bullet::draw() {
  if (isDead()) 
    return;
  // predefined sugar
  float &direction = m_direction.value;
  float texWidth = s_texture.width;
  float texHeight = s_texture.height;

  float scale = 20.f; // rudimentary
  DrawTexturePro
  (
    s_texture, // texture
    {0.f, 0.f, texWidth, texHeight}, // src
    {(m_body.x + 0.5f) * scale, (m_body.y + 0.5f) * scale, m_body.width * scale, m_body.height * scale}, // dest
    {m_body.width * 0.5f * scale, m_body.height * 0.5f * scale}, // origin
    (direction - M_PI*0.5)/M_PI*180, // rotation
    m_color // color
  ); 
}


OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Body, m_body)
OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Direction, m_direction)
OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Speed, m_speed)