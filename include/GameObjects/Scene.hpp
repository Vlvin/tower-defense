#pragma once
#include <vector>
#include <memory>

#include <GameObjects/GameObject.hpp>
#include <GameObjects/IUpdatable.hpp>
#include <GameObjects/IDrawable.hpp>

class Scene : public GameObject, public IUpdatable, public IDrawable
{
public:
  Scene();
  void pushObject(std::shared_ptr<GameObject> object);
  void clear();

  virtual void update(double deltaTime, CameraObject& camera) override;

  virtual void draw(CameraObject& camera) override;

protected:
  std::vector<std::shared_ptr<GameObject>> m_objects;
public:
  auto begin() -> decltype(m_objects.begin());
  auto end() -> decltype(m_objects.end());
};
