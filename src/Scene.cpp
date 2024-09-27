#include <GameObjects/Scene.hpp>
#include <GameObjects/IGameObject.hpp>
#include <algorithm>
#include <LayerValues.hpp>

Scene::Scene() // for some unknown reason Scene is coupled to be IGameObject
  : IGameObject(SCENE_DRAW_LAYER)
{
  m_objects = {};
}


void Scene::pushObject(std::shared_ptr<IGameObject> object) {
  m_objects.push_back(object);
}

void Scene::clear() {
  m_objects.clear();
}

void Scene::update(double deltaTime, CameraObject& camera) {
  for (size_t i = 0; i < m_objects.size(); i++) {

    // update
    m_objects[i]->update(deltaTime, camera);

    // check if we destroyed this scene by clicking exit button
    if (WindowShouldClose()) return;
    
    // check if object chose to be deleted
    if (m_objects[i]->isDead()) {
      m_objects[i] = m_objects.back();
      m_objects.pop_back();
      i--; 
    }
  } //vector
}

void Scene::draw(CameraObject& camera) {
  std::sort (
    m_objects.begin(),
    m_objects.end(),
    [] (
      std::shared_ptr<IGameObject> &left,
      std::shared_ptr<IGameObject> &right
    ) {
      return left->getLayer() < right->getLayer();
    }
  );
  for (auto &object : m_objects) {
    object->draw(camera);
  }
}


auto Scene::begin() -> decltype(m_objects.begin()) {
  return m_objects.begin();
}

auto Scene::end() -> decltype(m_objects.end()) {
  return m_objects.end();
}