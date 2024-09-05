#include <PlayerHUD.hpp>
#include <GameObjects/Player.hpp>
#include <raylib.h>
#include <string>

PlayerHUD::PlayerHUD() {}

void PlayerHUD::draw(Player& player) {

  DrawRectangleRec(
    {1.f, 1.f, 25.f, 25.f},
    YELLOW
  ); // money

  DrawRectangleRec(
    {1.f, 27.f, 25.f, 25.f},
    RED
  ); // health
  player.dispatch([] (::components::Health& health, ::components::Money& money) {
    DrawText(std::to_string(money.value).c_str(), 27, 1, 25, WHITE);
    DrawText(std::to_string(money.value).c_str(), 27, 27, 25, WHITE);
  });
}