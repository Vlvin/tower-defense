#pragma once
#include <vector>

class Scene;

class SceneManager {
public:

  static SceneManager& Get();

  static void PushScene(Scene& scene); // retranslator
  static void PopScene(); // retranslator
  static void Update(double deltaTime); // retranslator
  static void Draw(); // retranslator

  SceneManager(SceneManager&) = delete;
  SceneManager &operator=(SceneManager&) = delete;
private:
  void internPushScene(Scene& scene);
  void internPopScene();
  void internUpdate(double deltaTime);
  void internDraw();

  std::vector<Scene&> m_scenes; // stack of scenes
  /**
   * PushScene
   * PopScene
   * Update
   * Draw
  */
  SceneManager();
};