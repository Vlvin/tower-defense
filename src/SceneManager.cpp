#include <SceneManager.hpp>
#include <iostream>
#include <Scene.hpp>

void SceneManager::PushScene(Scene &scene) {
  m_scenes.push_back(scene);
}

void SceneManager::PopScene() {
  if (!m_scenes.empty()) // useless cause all actions called from SceneManager::Back().update
    m_scenes.back().clear();
  m_scenes.pop_back();
  if (m_scenes.empty()) 
    CloseWindow();
}

void SceneManager::Update(double deltaTime) {
  if (m_scenes.empty()) return;
  m_scenes.back().update(deltaTime);
}

void SceneManager::Draw() {
  if (m_scenes.empty()) return;
  m_scenes.back().draw();
}

Scene &SceneManager::Back() {
  if (m_scenes.empty()) 
    throw std::out_of_range("No Scenes in manager");
  return m_scenes.back();
}

