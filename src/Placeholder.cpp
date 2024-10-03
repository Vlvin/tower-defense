#include <GameObjects/Placeholder.hpp>
#include <Game.hpp>
#include <GameObjects/Tourel.hpp>
#include <InputHandler.hpp>
#include <LayerValues.hpp>
#include <nlohmann/json.hpp>
#include <fstream>


Texture PlaceHolder::s_texture{
  0,
  0,
  0,
  0,
  0
};

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
        if (object->dispatch([] (::components::PlayerTag&) {})) {
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
  if (!s_texture.width) {
    nlohmann::json config;

    std::fstream configFile("config.json", std::ios::in);

    configFile >> config; 

    std::string texPath = config["installPath"].get<std::string>() + "assets/PlaceHolder.png";
    configFile.close();
    const char* tPCS = texPath.c_str();
    auto im = LoadImage(tPCS);
    s_texture = LoadTextureFromImage(im);
    UnloadImage(im);
  }
  setLayer(PLACEHOLDER_DRAW_LAYER);
  setColor(WHITE);
}

bool PlaceHolder::getMouseCollision(CameraObject& camera) {
  auto body = getBody();
  auto renderBody = Rectangle{
    (body.x - camera.getPosition().x - 0.5f) * camera.getScale(),
    (body.y - camera.getPosition().y - 0.5f) * camera.getScale(),
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
  // DrawRectangleRec(renderBody, getColor());
  float texWidth = s_texture.width;
  float texHeight = s_texture.height;
  float &scale = camera.getScale();
  Vector2 &camPos = camera.getPosition();
  auto renderBody = Rectangle{
    (body.x - camPos.x) * scale,
    (body.y - camPos.y) * scale,
    body.width * scale,
    body.height * scale
  };
  DrawTexturePro
  (
    s_texture, // texture
    {0.f, 0.f, texWidth, texHeight}, // src
    renderBody, // dest
    {renderBody.width * 0.5f, renderBody.height * 0.5f}, // origin
    0.f, // rotation
    getColor() // color
  ); 
}