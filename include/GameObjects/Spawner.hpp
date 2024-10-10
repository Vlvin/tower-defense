
#include <GameObjects/GameObject.hpp>
#include <GameObjects/IUpdatable.hpp>
class ICloneable;


class Spawner : public GameObject, public IUpdatable {
public:
  Spawner(std::unique_ptr<ICloneable> object);

  void setSpawnTarget(std::unique_ptr<ICloneable> object);

  void spawn();

  void update(double deltaTime, CameraObject& camera) override;
protected:
  std::unique_ptr<ICloneable> m_object;
};