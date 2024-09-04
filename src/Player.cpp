#include <GameObjects/Player.hpp>
#include <PlayerHUD.hpp>
#include <Game.hpp>

Player::Player()
: IGameObject(HUD_DRAW_LAYER) {

  m_playerHUD = new PlayerHUD();
}

Player::~Player() {
  delete m_playerHUD;
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

