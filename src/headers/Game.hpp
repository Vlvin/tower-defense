#include <SceneManager.hpp>
#include <MyCamera.hpp>
#include <Player.hpp>

/**
 * Because there are only two solutions to this problem
 * Adding parent thing to every object in this project
 * or Singleton
 ```
 ```
 * So I introduce you Game Singleton, 
 * which stores all things that I want to keep in "global access",
 * But want to be able to restart game on every moment
 ```
 ```
 * Here you have 3 instance related methods instead of 1
 ```
 Game::Init() 
 ``` 
 * is used to create new instance, 
 * you can call it before Init or after Shutdown
 ```
 Game::Shutdown() 
 ``` 
 * is used to remove old instance and reset state of Game, 
 * you can call it only after Init
 ```
 Game::Instance() 
 ``` 
 * is used to get instance, 
 * you can call it after Init and before Shutdown
*/
class Game {
public:
  static Game& Instance();
  static void Init();
  static void Run();
  static void Quit();

  static SceneManager &GetSceneManager();
  static Player &GetPlayer();
  static CameraObject &GetCamera();

  Game(Game&) = delete;
  Game operator=(Game&) = delete;
protected:
  Game();

  void internRun();
  
private:
  inline static Game *s_instance = nullptr;
  SceneManager m_sceneManager;
  Player m_player;
  CameraObject m_camera;
};