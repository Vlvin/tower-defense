#include <Game.hpp>
#include <unistd.h>
#include <Debug.h>


Game::Game(InputHandler& input) 
  : m_input(input), m_camera(input, .01f, .01f)
{}


Game& Game::Instance() {
  // call only after Init
  DASSERT(s_instance.get());

  return *s_instance;
}

void Game::Init(InputHandler& input) {
  // call only before Init or after Shutdown
  DASSERT(s_instance.get() == nullptr);

  s_instance = std::shared_ptr<Game>(new Game(input));
}

void Game::Run() {
  Instance().internRun();
}

void Game::Quit() {
  // call only after Init
  DASSERT(s_instance.get());
  
  s_instance = {nullptr};
}


SceneManager &Game::GetSceneManager() {
  return Instance().m_sceneManager;
}

Player &Game::GetPlayer() {
  return Instance().m_player;
}

// CameraObject &Game::GetCamera() {
//   return Instance().m_camera;
// }

void Game::internRun() {
  double delta, time, FPS = 60, desDelta = 1000/FPS;


  InitWindow(640, 480, "Test");
  // raylib setub must go after InitWindow
  SetExitKey(KEY_NULL);

  while(!WindowShouldClose()) 
  {

    #pragma region UPDATE
    m_camera.update(delta);
    if (!m_sceneManager.Update(delta, m_camera))
      break;
    #pragma endregion UPDATE
    
    m_sceneManager.Draw(m_camera);  
    
    #pragma region TIME
    delta = (GetTime() - time) * 1000;    
    time = GetTime();
    if (desDelta > delta)
      usleep((desDelta - delta) * 1000);
    #pragma endregion TIME
  }
}
