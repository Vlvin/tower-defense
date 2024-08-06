#pragma once
#include <vector>
#include <memory>
#include <Scene.hpp>

class Scene;

class SceneManager {
public:

  static SceneManager& Get();

  static void PushScene(Scene &scene); // retranslator
  static void PopScene(); // retranslator
  static void Update(double deltaTime); // retranslator
  static void Draw(); // retranslator
  static Scene &Back(); // retranslator

  SceneManager(SceneManager&) = delete;
  SceneManager &operator=(SceneManager&) = delete;
private:
  void internPushScene(Scene &scene);
  void internPopScene();
  void internUpdate(double deltaTime);
  void internDraw();
  Scene &internBack();

  std::vector<Scene> m_scenes; // stack of scenes
  SceneManager();
};