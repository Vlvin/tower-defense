#include <memory>

#include <SceneManager.hpp>
#include <CameraObject.hpp>
#include <Player.hpp>

/**
 * Because there are only two solutions to this problem
 * Adding parent thing to every object in this project
 * or Singleton
 ```
 ```
 * So I introduce you Game Singleton, (which is not exaclty GoF Singleton)
 * which stores all things that I want to keep in "global access",
 * But want to be able to restart game on every moment
 * So here you have 3 instance related methods instead of 1
*/
class Game {
public:
  /**
   * Instance() is used to get instance, 
   * you can call it after Init and before Shutdown
  */
  static Game& Instance();
  /**
   * Init() is used to create new instance, 
   * you can call it before Init or after Shutdown
  */
  static void Init();
  /**
   * Quit() is used to remove old instance of Game, 
   * you can call it only after Init
  */
  static void Quit();

  static void Run();

  static SceneManager &GetSceneManager();
  static Player &GetPlayer();
  static CameraObject &GetCamera();

  Game(Game&) = delete;
  Game operator=(Game&) = delete;
protected:
  Game();
  void internRun();
  
protected:
  SceneManager m_sceneManager;
  Player m_player;
  CameraObject m_camera;
  
private:
  inline static std::shared_ptr<Game> s_instance = nullptr;
};