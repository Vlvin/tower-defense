#include "Scene.hpp"
#include "IGameObject.hpp"

Scene::Scene() 
{

}


void Scene::pushObject(std::shared_ptr<IGameObject> object) {
  m_objects.push_back(object);
}

void Scene::clear() {
  m_objects.clear();
}

void Scene::update(double deltaTime) {
  for (auto &object : m_objects) {
    object->update(deltaTime);
  }
}

void Scene::draw() {
  for (auto &object : m_objects) {
    object->draw();
  }
}
