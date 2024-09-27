#include <GameObjects/IGameObject.hpp>


class Spawner : public IGameObject {
public:
  Spawner(std::unique_ptr<IGameObject> object);
  void setSpawnTarget(std::unique_ptr<IGameObject> object);
  void spawn();
  void update(double deltaTime, CameraObject& camera) override;
  void draw(CameraObject& camera) override;
protected:
  std::unique_ptr<IGameObject> m_object;
};