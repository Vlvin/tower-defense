#pragma once
#include <Node.hpp>
#include <Components.hpp>

class CameraObject;

class GameObject {
public:
  GameObject(uint8_t layer);

  template <class CompType>
  CompType *get() {
    return get_(tag<CompType>{});
  }
      
  // dispatch : tries to call f with all of the components it requires
  // Returns whether all components were found and f was called.
  template <class F>
  bool dispatch(F &&f) {
    return dispatch_(
      std::forward<F>(f), 
      typename params<std::decay_t<F>>::type{}
    );
  }
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
  bool dispatch_(F &&f, tag<Params...>) {

      bool allGood = true;

      // Construct a tuple with the component pointers
      // For each component required by f:
      auto ptrs = std::make_tuple([&]() -> std::decay_t<Params>* {
          
          // One component is already missing, skip the rest
          if(!allGood)
          return nullptr;
          
          // Get the component of the adequate type
          auto *comp = get<std::decay_t<Params>>();
          
          // Failure: break the chain
          if(!comp)
          allGood = false;
              
          return comp;
      }()...);

      // Missing component, bail out
      if(!allGood)
          return false;

      // Call f with the dereferenced pointers
      derefCall(std::forward<F>(f), ptrs, std::index_sequence_for<Params...>{});
      return true;
  }
  Node m_node;
  bool m_isDead;
};