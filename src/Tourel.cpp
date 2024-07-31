#include <Tourel.hpp>
#include <SceneManager.hpp>
#include <ColorTools.hpp>

Texture Tourel::s_texture = {
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
  m_directionAngle = {0.f};
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
  auto &parent = SceneManager::Back();
  auto &tourelDir = m_directionAngle.value;
  auto tourelPos = this->getPosition();
  // summon new bullet which moves to target with m_bullet speed and body
  m_bullet.dispatch(
    [&] (components::Direction& dir, components::Body& body) {
      auto bullet = std::make_shared<Bullet>(
        (Rectangle){tourelPos.x, tourelPos.y, body.width, body.height}, 
        tourelDir
      );
      parent.pushObject(bullet);
    }
  );
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


  

  float &direction = m_directionAngle.value;
  Rectangle &body = m_body;

  
  m_target->dispatch([&] (
    // arguements
    components::Body &tBody, 
    components::Speed &tSpeed, 
    components::Direction &tDirection
  ) {
    // body
    /**
     * future: predict m_target position after optimal shoot time
     * 
     * now: look at m_target
    */
    direction = atan2(
      body.y - tBody.y,
      body.x - tBody.x
    );
  });


  shoot();
}

void Tourel::draw() {
  // predefined sugar
  float &direction = m_directionAngle.value;
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

OBJECT_OVERRIDE_COMPONENT_CPP(Tourel, Body, m_body)
OBJECT_OVERRIDE_COMPONENT_CPP(Tourel, Direction, m_directionAngle)