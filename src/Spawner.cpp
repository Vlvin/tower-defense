#include <GameObjects/Spawner.hpp>
#include <LayerValues.hpp>
#include <Game.hpp>


Spawner::Spawner(std::unique_ptr<IGameObject> object) 
  : m_object(std::move(object)), IGameObject(SPAWNER_DRAW_LAYER) {}


void Spawner::setSpawnTarget(std::unique_ptr<IGameObject> object) {
  m_object = std::move(object);
}

void Spawner::spawn() {
  auto &parent = Game::GetSceneManager().Back();
  parent.pushObject(m_object->clone());
}


void Spawner::update(double deltaTime, CameraObject& camera) {
  
}

void Spawner::draw(CameraObject& camera) {
  
}
