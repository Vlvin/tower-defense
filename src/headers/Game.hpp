#include <SceneManager.hpp>
#include <MyCamera.hpp>
#include <Player.hpp>

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
  Player m_player; // dereference after including Player
  CameraObject m_camera; // dereference after including Player
};