#pragma once

#include <iostream>
#include <random>
#include <stdexcept>
#include <memory>
#include <cstdint>

#include <raylib.h>
#include <Node.hpp>
#include <Components.hpp>

class CameraObject;

class GameObject {
public:
  GameObject(uint8_t layer);

  template <class CompType>
  CompType *get();
      
  // dispatch : tries to call f with all of the components it requires
  // Returns whether all components were found and f was called.
  template <class F>
  bool dispatch(F &&f);
  /**
   * Future components definition
   * macro adds virtual function returns compType pointer
   * which is now just nullpointer
  */

  bool isDead();
  uint8_t getLayer();
  
protected:
  void setLayer(uint8_t layer);

#define OBJECT_DECLARE_COMPONENT(CompType) \
  virtual ::components::CompType *get_(tag<::components::CompType>) { return nullptr; }
  
  OBJECT_DECLARE_COMPONENT(Money);
  OBJECT_DECLARE_COMPONENT(Health);
  OBJECT_DECLARE_COMPONENT(Speed);
  OBJECT_DECLARE_COMPONENT(Direction);
  OBJECT_DECLARE_COMPONENT(Body);
  OBJECT_DECLARE_COMPONENT(EnemyTag);
  OBJECT_DECLARE_COMPONENT(PlayerTag);

#undef OBJECT_DECLARE_COMPONENT

  template <class F, class... Params>
  bool dispatch_(F &&f, tag<Params...>);
  Node m_node;
  bool m_isDead;
};