#include <GameObjects/Spawner.hpp>
#include <GameObjects/ICloneable.hpp>
#include <LayerValues.hpp>
#include <Game.hpp>
#include <GameObjects/Map.hpp>


Spawner::Spawner(double interval, size_t amount, std::shared_ptr<ICloneable> object) 
  : GameObject(SPAWNER_DRAW_LAYER), 
  m_interval(interval),
  m_lastSpawned(GetTime()),
  m_amount(amount),
  m_object(object){}


void Spawner::setSpawnTarget(std::shared_ptr<ICloneable> object) {
  m_object = object;
}

inline void Spawner::spawn() {
  auto &parent = Game::GetSceneManager().Back();
  auto object = std::dynamic_pointer_cast<GameObject>(m_object->clone());
  parent.pushObject(object);
}


void Spawner::update(double deltaTime, CameraObject& camera) {
  if (GetTime() - m_lastSpawned >= m_interval) {
    m_lastSpawned = GetTime();
    spawn();
  }
}

void Spawner::incIntervalBy(double value) {
  if (value < 0 && m_interval < -value)
    m_interval = 0;
  else
    m_interval += value;
}
void Spawner::incAmountBy(int value) {
  if (value < 0 && m_interval < -value)
    m_amount = 0;
  else
    m_amount += value;

}