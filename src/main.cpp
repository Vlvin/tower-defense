#include <SceneManager.hpp>
#include <Scene.hpp>
#include <Button.hpp>
#include <Tourel.hpp>
#include <Tiler.hpp>
#include <Map.hpp>
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {
  // Buttons
  auto quitScene = std::make_shared<Button>(
    (Rectangle){25., 25., 25., 25.},
    SceneManager::PopScene,
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
    SceneManager::PushScene(settings);
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

  
  SceneManager::PushScene(main);

  double delta, time, FPS = 60, desDelta = 1000/FPS;

  InitWindow(640, 480, "Test");


  while(!WindowShouldClose()) 
  {
    // SceneManager::Update(delta) Is allowed to close window
    BeginDrawing(); 
      ClearBackground(BLACK);
      SceneManager::Draw();
    EndDrawing();


    delta = (GetTime() - time) * 1000;
    
    time = GetTime();

    if (desDelta > delta)
      usleep((desDelta - delta) * 1000);

    SceneManager::Update(delta);
  }
}