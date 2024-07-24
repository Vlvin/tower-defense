#include <SceneManager.hpp>
#include <Scene.hpp>
#include <Button.hpp>
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
    
    settings.pushObject(quitScene);
    settings.pushObject(map);
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
    delta = (GetTime() - time) * 1000;
    
    time = GetTime();
    if (desDelta > delta)
    {
      usleep((desDelta - delta) * 1000);
    }


    BeginDrawing();
    SceneManager::Update(delta);
    if (WindowShouldClose()) break;

      ClearBackground(BLACK);
      SceneManager::Draw();
    EndDrawing();

  }
}