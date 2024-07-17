#include "SceneManager.hpp"
#include <iostream>

#include "Scene.hpp"


SceneManager& SceneManager::Get() {
  // Now this has even no instance member
  static SceneManager s_instance;
  return s_instance;
}

void SceneManager::PushScene(Scene scene) {
  return Get().internPushScene(scene);
}
void SceneManager::PopScene() {
  return Get().internPopScene();
}
void SceneManager::Update(double deltaTime) {
  return Get().internUpdate(deltaTime);
}
void SceneManager::Draw() {
  return Get().internDraw();
}
Scene &SceneManager::Back() {
  return Get().internBack();
}

void SceneManager::internPushScene(Scene scene) {
  m_scenes.push_back(scene);

}

void SceneManager::internPopScene() {
  m_scenes.pop_back();
  if (m_scenes.empty()) CloseWindow();
}


void SceneManager::internUpdate(double deltaTime) {
  if (m_scenes.empty()) return;
  m_scenes.back().update(deltaTime);
}

void SceneManager::internDraw() {
  if (m_scenes.empty()) return;
  m_scenes.back().draw();
}

Scene &SceneManager::internBack() {
  if (m_scenes.empty()) 
    throw std::out_of_range("No Scenes in manager");
  return m_scenes.back();
}

SceneManager::SceneManager() {
}

