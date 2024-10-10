#include <GameObjects/Spawner.hpp>
#include <GameObjects/ICloneable.hpp>
#include <LayerValues.hpp>
#include <Game.hpp>


Spawner::Spawner(std::unique_ptr<ICloneable> object) 
  : m_object(std::move(object)), GameObject(SPAWNER_DRAW_LAYER) {}


void Spawner::setSpawnTarget(std::unique_ptr<ICloneable> object) {
  m_object = std::move(object);
}

void Spawner::spawn() {
  auto &parent = Game::GetSceneManager().Back();
  auto object = std::dynamic_pointer_cast<GameObject>(m_object->clone());
  parent.pushObject(object);
}


void Spawner::update(double deltaTime, CameraObject& camera) {
  
}
