// here you must have IGameObject with update delegation to PlayerBehaviour
#pragma once
#include <GameObjects/IGameObject.hpp>

class PlayerHUD;

class Player : public IGameObject {
public:
  Player();
  ~Player();
  virtual void update(double deltaTime, CameraObject& camera) override;
  virtual void draw(CameraObject& camera) override;

protected:
  PlayerHUD *m_playerHUD;

  ::components::Health m_health;
  ::components::Money m_money;

protected:
  OBJECT_OVERRIDE_COMPONENT_H(Health)
  OBJECT_OVERRIDE_COMPONENT_H(Money)
};