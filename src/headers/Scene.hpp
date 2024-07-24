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
  /**
   * Change reference on something different
   * like pointer or direct instance
   * cause you'll create object 
   * and destruct it after passing a reference
  */
  std::vector<std::shared_ptr<IGameObject>> m_objects;
};
