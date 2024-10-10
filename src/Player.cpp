#include <GameObjects/Player.hpp>
#include <PlayerHUD.hpp>
#include <Game.hpp>
#include <LayerValues.hpp>

Player::Player()
: GameObject(HUD_DRAW_LAYER) {

  m_playerHUD = new PlayerHUD();

  m_health = {20};
  m_money = {20};
}

Player::~Player() {
  delete m_playerHUD;
}

bool Player::withdraw(uint money) {
  if (m_money.value >= money) {
    m_money.value -= money;
    return true;
  }
  return false;
}

void Player::topUp(uint money) {
  m_money.value += money;
}

void Player::update(double deltaTime, CameraObject& camera) {
  if (m_health.value <= 0)
    m_isDead = true;

  if (m_isDead)
    Game::GetSceneManager(); /* push gameover */
}

void Player::draw(CameraObject& camera) {
  m_playerHUD->draw(*this);
}


OBJECT_OVERRIDE_COMPONENT_CPP(Player, Health, m_health)
OBJECT_OVERRIDE_COMPONENT_CPP(Player, Money, m_money)
OBJECT_OVERRIDE_COMPONENT_CPP(Player, PlayerTag, m_tag)

