#include <GameObjects/Scene.hpp>
#include <SceneManager.hpp>
#include <iostream>

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

bool SceneManager::Update(double deltaTime, CameraObject& camera) {
  if (m_scenes.empty()) return false;
  m_scenes.back().update(deltaTime, camera);
  return !m_scenes.empty();
}

void SceneManager::Draw(CameraObject& camera) {
  if (m_scenes.empty()) return;
  BeginDrawing(); 
    ClearBackground(BLACK);
    m_scenes.back().draw(camera);
  EndDrawing();
}

Scene &SceneManager::Back() {
  if (m_scenes.empty()) 
    throw std::out_of_range("No Scenes in manager");
  return m_scenes.back();
}

