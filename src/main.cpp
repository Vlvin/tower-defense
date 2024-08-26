#include <SceneManager.hpp>
#include <Scene.hpp>
#include <Game.hpp>
#include <Button.hpp>
#include <Tourel.hpp>
#include <Tiler.hpp>
#include <Map.hpp>
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {

  Game::Init();
  // Buttons
  auto quitScene = std::make_shared<Button>(
    (Rectangle){25., 25., 25., 25.},
    [] {Game::GetSceneManager().PopScene();},
    RED 
  );

  auto loadLevel = [&]() {
    Scene settings;
    auto map = Map::loadFromFile("level/demo/map.ppm");
    auto tiler = std::make_shared<Tiler>("assets/tilemap-32.png");
    map->attachTiler(tiler);
    auto shooter = std::make_shared<Tourel>(
      (Rectangle){10.f, 10.f, 1.f, 1.f},
      4.f,
      Bullet({1.f, 1.f, .1f, .1f}, 0.f)
    );
    settings.pushObject(quitScene);
    settings.pushObject(map);
    settings.pushObject(shooter);
    Game::GetSceneManager().PushScene(settings);
  };


  auto enterLevel = std::make_shared<Button>(
    (Rectangle){100., 200., 440., 50.},
    loadLevel,
    GREEN
  );

  // MainScene
  Scene main;
  main.pushObject(quitScene);
  main.pushObject(enterLevel);

  
  Game::GetSceneManager().PushScene(main);

  Game::Run();

  Game::Quit();
}