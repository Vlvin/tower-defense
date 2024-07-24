#pragma once
#include <vector>
#include <memory>

#include <IGameObject.hpp>



class Scene : public IGameObject
{
public:
  Scene();
  void pushObject(std::shared_ptr<IGameObject> object);
  void clear();
  virtual void update(double deltaTime) override;
  virtual void draw() override;
protected:
  std::vector<std::shared_ptr<IGameObject>> m_objects;
public:
  auto begin() -> decltype(m_objects.begin());
  auto end() -> decltype(m_objects.end());
};
