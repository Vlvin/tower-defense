#pragma once
#include <vector>
#include <memory>
#include <Scene.hpp>

class Scene;

class SceneManager {
public:

  void PushScene(Scene &scene);
  void PopScene(); 
  void Update(double deltaTime);
  void Draw();
  Scene &Back();
private:

  std::vector<Scene> m_scenes; // stack of scenes
};