#pragma once
#include <vector>
#include <memory>

class Scene;

class SceneManager {
public:

  static SceneManager& Get();

  static void PushScene(std::shared_ptr<Scene> scene); // retranslator
  static void PopScene(); // retranslator
  static void Update(double deltaTime); // retranslator
  static void Draw(); // retranslator

  SceneManager(SceneManager&) = delete;
  SceneManager &operator=(SceneManager&) = delete;
private:
  void internPushScene(std::shared_ptr<Scene> scene);
  void internPopScene();
  void internUpdate(double deltaTime);
  void internDraw();

  std::vector<std::shared_ptr<Scene>> m_scenes; // stack of scenes
  /**
   * PushScene
   * PopScene
   * Update
   * Draw
  */
  SceneManager();
};