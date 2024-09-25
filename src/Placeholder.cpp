#include <GameObjects/Placeholder.hpp>
#include <Game.hpp>
#include <GameObjects/Tourel.hpp>
#include <InputHandler.hpp>

PlaceHolder::PlaceHolder(InputHandler& input, Vector2 position)
  : Button(
    input, 
    Rectangle{position.x, position.y, 1.f, 1.f},
    [position] {
      auto& parent = Game::GetSceneManager().Back(); 
      //temp
      DLOG(position.x << ":" << position.y);
      int tourelCost = 5;

      std::shared_ptr<IGameObject> player{nullptr};
      for (auto object : parent) {
        if (object->dispatch([] (::components::PlayerTag&) {
        })) {
          player = object;
          break;
        }
      }

      if (!player.get())
        return;

      DLOG("Player " << player.get());

      if (!std::dynamic_pointer_cast<Player>(player)->withdraw(tourelCost))
        return;

      
      auto tourel = std::make_shared<Tourel>(
        Rectangle{position.x, position.y, 1.f, 1.f},
        3.f,
        Bullet({1.f, 1.f, .5f, .5f}, 0.f)
      );

      parent.pushObject(tourel);
    }
  )
{
  setLayer(PLACEHOLDER_DRAW_LAYER);
  setColor(WHITE);
}

bool PlaceHolder::getMouseCollision(CameraObject& camera) {
  auto body = getBody();
  auto renderBody = Rectangle{
    (body.x - camera.getPosition().x) * camera.getScale(),
    (body.y - camera.getPosition().y) * camera.getScale(),
    body.width * camera.getScale(),
    body.height * camera.getScale()
  };
  Vector2 mousePos = input.getMousePosition();
  return (
  (
    mousePos.x > (renderBody.x) && 
    mousePos.x < (renderBody.x + renderBody.width)
  ) 
  &&
  (
    mousePos.y > (renderBody.y) && 
    mousePos.y < (renderBody.y + renderBody.height)
  )
  );
}

void PlaceHolder::draw(CameraObject &camera) {
  auto body = getBody();
  auto renderBody = Rectangle{
    (body.x - camera.getPosition().x) * camera.getScale(),
    (body.y - camera.getPosition().y) * camera.getScale(),
    body.width * camera.getScale(),
    body.height * camera.getScale()
  };
  DrawRectangleRec(renderBody, getColor());
}