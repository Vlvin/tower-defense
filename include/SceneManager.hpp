#pragma once
#include <vector>
#include <memory>
#include <GameObjects/Scene.hpp>

class Scene;

class SceneManager {
public:

  void PushScene(Scene &scene);
  void PopScene(); 
  bool Update(double deltaTime, CameraObject& camera);
  void Draw(CameraObject& camera);
  Scene &Back();
private:

  std::vector<Scene> m_scenes; // stack of scenes
};