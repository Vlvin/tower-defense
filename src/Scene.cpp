#include "Scene.hpp"
#include "IGameObject.hpp"
#include <algorithm>

Scene::Scene() 
  : IGameObject(SCENE_DRAW_LAYER)
{

}


void Scene::pushObject(std::shared_ptr<IGameObject> object) {
  m_objects.push_back(object);

  std::sort
  (
    m_objects.begin(),
    m_objects.end(),
    []
    (
      std::shared_ptr<IGameObject> &left, 
      std::shared_ptr<IGameObject> &right
    )
    {
      return left->getLayer() < right->getLayer();
    }
  );
}

void Scene::clear() {
  m_objects.clear();
}

void Scene::update(double deltaTime) {
  for (size_t i = 0; i < m_objects.size(); i++) 
  {
    m_objects[i]->update(deltaTime);
    if (m_objects[i]->isDead()) 
    {
      m_objects[i] = std::move(m_objects.back());
      m_objects.pop_back();
      i--; 
    }
  }
}

void Scene::draw() {
  for (auto &object : m_objects) {
    object->draw();
  }
}
