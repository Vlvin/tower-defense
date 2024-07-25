#include <Bullet.hpp>


Texture Bullet::s_texture = {
  0,
  0,
  0,
  0,
  0
};

Bullet::Bullet(Rectangle body) 
  : IGameObject(BULLET_DRAW_LAYER) 
{  
  if (!s_texture.width) {
    auto image = LoadImage("assets/Tourel.png");
    s_texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }
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

}

void Bullet::draw() {

}


OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Body, m_body)
OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Direction, m_direction)
OBJECT_OVERRIDE_COMPONENT_CPP(Bullet, Speed, m_speed)