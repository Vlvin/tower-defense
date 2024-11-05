
#include <GameObjects/GameObject.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <memory>
class ICloneable;
class Map;

class Spawner : public GameObject, public IUpdatable {
public:
  /// @param interval - interval between spawns
  /// @param amount - how many copies of object to make at a time
  /// @param object - object to spawn
  Spawner(double interval, size_t amount, std::shared_ptr<ICloneable> object);

  void setSpawnTarget(std::shared_ptr<ICloneable> object);

  void spawn();

  void incIntervalBy(double value);
  void incAmountBy(int value);

  void update(double deltaTime, CameraObject& camera) override;
protected:
  double m_interval, m_lastSpawned;
  size_t m_amount;
  std::shared_ptr<ICloneable> m_object;
};