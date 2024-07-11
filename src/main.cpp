#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "Map.hpp"
#include <iostream>

int main(int argc, char** argv) {

  // Buttons
  auto quitScene = std::make_shared<Button>
  (
    Button
    (
      (Rectangle){25., 25., 25., 25.},
      SceneManager::PopScene
    ),
    RED
  );

  auto settingsFun = [&]()
  {
    auto settings = std::make_shared<Scene>();
    auto map = Map::loadFromFile("level/demo/map.ppm");
    
    
    settings->pushObject(quitScene);
    settings->pushObject(map);
    SceneManager::PushScene(settings);
  };


  auto enterSettings = std::make_shared<Button>
  (
    Button
    (
      (Rectangle){100., 200., 440., 50.},
      settingsFun
    ),
    GREEN
  );

  // MainScene
  auto main = std::make_shared<Scene>();
  main->pushObject(quitScene);
  main->pushObject(enterSettings);

  
  SceneManager::PushScene(main);

  double delta, time;

  InitWindow(640, 480, "Test");

  while(!WindowShouldClose()) 
  {
    delta = (GetTime() - time) * 1000;
    time = GetTime();

    BeginDrawing();
    SceneManager::Update(delta);
    if (WindowShouldClose()) break;

      ClearBackground(BLACK);
      SceneManager::Draw();
    EndDrawing();

  }
}