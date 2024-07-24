#include <Tourel.hpp>
#include <SceneManager.hpp>
#include <ColorTools.hpp>

Texture Tourel::s_texture{
  0,
  0,
  0,
  0,
  0
};


Tourel::Tourel(Rectangle body, float rangeOfAction, Bullet bullet)
  : IGameObject(TOUREL_DRAW_LAYER), m_bullet(std::move(bullet))
{
  if (!s_texture.width) {
    auto image = LoadImage("assets/Tourel.png");
    s_texture = LoadTextureFromImage(image);
    UnloadImage(image);
  }
  m_rangeOfAction = rangeOfAction;
  m_body = body;
  m_target = {nullptr};
  m_color = m_persistent = WHITE;
}

Tourel::Tourel(const Tourel &tourel, Color color)
  : Tourel(tourel)
{
  m_color = m_persistent = color;
}

void Tourel::shoot() {
  // summon new bullet which moves to target with m_bullet speed and body
  std::cout << "shoot to " << m_target << " at " << GetTime() << '\n';
}

void Tourel::locateTarget() {
  auto &parent = SceneManager::Back();
  auto tourelPos = this->getPosition();
  float radius = this->m_rangeOfAction;
  m_target = nullptr;
  for (auto object = parent.begin(); object != parent.end(); object++) {
    (*object)->dispatch([&](components::EnemyTag&, components::Body &body) {
      if (CT::vec2Distance(tourelPos, { body.x, body.y }) <= radius)
        this->m_target = *object;
    });
    if (m_target) break;
  }
}

Vector2 Tourel::getPosition() {
  return { m_body.x, m_body.y };
}

void Tourel::update(double deltaTime) {
  bool tooFarToShoot = false;
  auto tourelPos = this->getPosition();
  float radius = this->m_rangeOfAction;
  if (m_target) {
    m_target->dispatch([&] (components::Body &body) {
      tooFarToShoot = (CT::vec2Distance(tourelPos, { body.x, body.y }) > radius);
    });
  }
  if ((!m_target) || (m_target->isDead()) || (tooFarToShoot))
    locateTarget();

  if (!m_target) 
    return;

  shoot();
}

void Tourel::draw() {
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

OBJECT_OVERRIDE_COMPONENT_CPP(Tourel, Body, m_body)