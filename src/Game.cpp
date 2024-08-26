#include <Game.hpp>
#include <cassert>
#include <unistd.h>

Game& Game::Instance() {
  // call only after Init
  assert(s_instance);

  return *s_instance;
}

void Game::Init() {
  // call only before Init or after Shutdown
  assert(s_instance == nullptr);

  s_instance = new Game();
}

void Game::Run() {
  Instance().internRun();
}

void Game::Quit() {
  // call only after Init
  assert(s_instance);

  delete s_instance;
  s_instance = nullptr;
}


SceneManager &Game::GetSceneManager() {
 return Instance().m_sceneManager;
}

Player &Game::GetPlayer() {
 return Instance().m_player;
}

CameraObject &Game::GetCamera() {
 return Instance().m_camera;
}

void Game::internRun() {
  double delta, time, FPS = 60, desDelta = 1000/FPS;

  InitWindow(640, 480, "Test");


  while(!WindowShouldClose()) 
  {
    // SceneManager::Update(delta) Is allowed to close window
    BeginDrawing(); 
      ClearBackground(BLACK);
      m_sceneManager.Draw();  
    EndDrawing();

    delta = (GetTime() - time) * 1000;
    
    time = GetTime();

    if (desDelta > delta)
      usleep((desDelta - delta) * 1000);

    m_sceneManager.Update(delta);
  }
}

Game::Game() {

}