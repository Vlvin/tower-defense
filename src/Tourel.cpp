#include <Tourel.hpp>
#include <SceneManager.hpp>
#include <ColorTools.hpp>
#include <cmath>

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



  m_bullet.dispatch([&] (components::Body& bulletBody) {
    bulletBody.x = body.x+0.5f;
    bulletBody.y = body.y+0.5f;
    DLOG("bulletBody.x" << bulletBody.x)
    DLOG("bulletBody.y" << bulletBody.y)
  });


  m_directionAngle = {0.f};
  m_rangeOfAction = rangeOfAction;
  m_body = body;
  m_target = {nullptr};
  m_color = m_persistent = WHITE;
  m_shootFreq = 0.1f;
  m_lastShot = GetTime() - m_shootFreq;
}

Tourel::Tourel(const Tourel &tourel, Color color)
  : Tourel(tourel)
{
  m_color = m_persistent = color;
}

void Tourel::shoot() {
  if ((GetTime() - m_lastShot) < m_shootFreq)
    return;

  auto &parent = SceneManager::Back();
  auto &tourelDir = m_directionAngle.value;
  // summon new bullet which moves to target with m_bullet speed and body
  m_bullet.dispatch(
    [&] (components::Direction& dir, components::Body& body) {

      auto bullet = std::make_shared<Bullet>(
        body, 
        tourelDir
      );
      parent.pushObject(bullet);
    }
  );
  m_lastShot = GetTime();
}

void Tourel::predictTargetPosition() {float &direction = m_directionAngle.value;
  Rectangle &body = m_body;


  float cannonX = 0.f;
  float cannonY = 0.f;
  float projSpeed = 0.f;

  m_bullet.dispatch([&] (
    components::Body &bBody, 
    components::Speed &bSpeed) {

    cannonX = bBody.x;
    cannonY = bBody.y;
    projSpeed = bSpeed.value;
  });
  DLOG("cannonX: " << cannonX)
  DLOG("cannonY: " << cannonY)
  DLOG("projSpeed: " << projSpeed)

  m_target->dispatch([&] (
    // arguements
    components::Body &tBody, 
    components::Speed &tSpeed, 
    components::Direction &tDirection) {
    // body
    /**
     * predict m_target position after optimal shoot time
    */
#pragma region init
    float a = 0., b = 0., c = 0., D = 0., t1 = 0., t2 = 0., actual_time = 0.;
    float targetAngle = tDirection.value;
    float targetConstantSpeed = tSpeed.value;
    float targetVelocityX = cos(targetAngle) * targetConstantSpeed;
    float targetVelocityY = sin(targetAngle) * targetConstantSpeed;
    float targetStartX = tBody.x;
    float targetStartY = tBody.y;
#pragma endregion init
    // ax^2 + bx + c = 0
    // x is time
#pragma region equasion
    a = pow(targetVelocityX, 2) + pow(targetVelocityY, 2) - pow(projSpeed, 2);
    b = 2 * (
          targetVelocityX * (targetStartX - cannonX)
        + targetVelocityY * (targetStartY - cannonY)
            );
    c = pow(targetStartX - cannonX, 2) + pow(targetStartY - cannonY, 2);
    D = pow(b, 2) - 4*a*c;
#pragma endregion equasion

    if (D < 0) return;
    t1 = (-b + sqrt(D))/(2*a);
    t2 = (-b - sqrt(D))/(2*a);

    actual_time = std::min(t1, t2);
    if (0. > t1) actual_time = t2;
    if (0. > t2) actual_time = t1;
    if (actual_time < 0) return;
    DLOG("actual_time: " << actual_time)
    
#ifdef NDEBUG
    this->predX = targetStartX - (targetVelocityX * actual_time);
    this->predY = targetStartY - (targetVelocityY * actual_time);
#else
    float predX = targetStartX - (targetVelocityX * actual_time);
    float predY = targetStartY - (targetVelocityY * actual_time);
#endif

    float deltaX = this->getPosition().x - predX;
    float deltaY = this->getPosition().y - predY;

    direction = atan2(deltaY, deltaX);
  });
  DLOG("direction: " << direction)
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

  
  predictTargetPosition();
  
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
#ifdef NDEBUG
  DrawRectangleRec({(predX) * scale, (predY) * scale, m_body.width * scale, m_body.height * scale}, PINK);
#endif
}

OBJECT_OVERRIDE_COMPONENT_CPP(Tourel, Body, m_body)
OBJECT_OVERRIDE_COMPONENT_CPP(Tourel, Direction, m_directionAngle)