#include <GameObjects/Scene.hpp>
#include <GameObjects/Button.hpp>
#include <GameObjects/Tourel.hpp>
#include <GameObjects/Map.hpp>
#include <GameObjects/Player.hpp>
#include <GameObjects/Placeholder.hpp>
#include <SceneManager.hpp>
#include <Game.hpp>
#include <Tiler.hpp>
#include <PhysicalInput.hpp>

#include <unistd.h>


int main(int argc, char** argv) {

  PhysicalInput input;
  Game::Init(input);

  // Buttons
  auto quitScene = std::make_shared<Button>(
    Button {
      input,
      (Rectangle){640 - 50.f, 25.f, 25.f, 25.f},
      [] {Game::GetSceneManager().PopScene();}
    },
    RED 
  );


  #ifdef NDEBUG
    #include <iostream>
    std::cout << "Fuck\n";
  #endif

  auto loadLevel = [&]() {
    Scene level;
    auto levelInfo = Map::loadLevelFromFile("level/demo/map.ppm", input);
    auto tiler = std::make_shared<Tiler>("assets/tilemap-32.png");

    levelInfo.map->attachTiler(tiler);
    auto player = std::make_shared<Player>();
    level.pushObject(quitScene);

    level.pushObject(levelInfo.map);
    level.pushObject(player);
    for (auto& object : levelInfo.staticObjects)
      level.pushObject(object);
    Game::GetSceneManager().PushScene(level);
  };


  auto enterLevel = std::make_shared<Button>(
    Button {
      input,
      (Rectangle){100., 200., 440., 50.},
      loadLevel
    },
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