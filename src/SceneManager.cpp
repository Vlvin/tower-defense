#include "SceneManager.hpp"
#include <iostream>

SceneManager& SceneManager::Get() {
  // Now this has even no instance member
  static SceneManager s_instance;
  return s_instance;
}

void SceneManager::PushScene(Scene& scene) {
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


void SceneManager::internPushScene(Scene& scene) {

}

void SceneManager::internPopScene() {

}

void SceneManager::internUpdate(double deltaTime) {

}

void SceneManager::internDraw() {

}




SceneManager::SceneManager() {
  std::cout << "Constructor\n";
}

