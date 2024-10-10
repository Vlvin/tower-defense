#include <GameObjects/GameObject.hpp>

GameObject::GameObject(uint8_t layer) 
    : m_node(layer), m_isDead(false)
{}

void GameObject::setLayer(uint8_t layer) {
    m_node.setLayer(layer);
}


uint_8 GameObject::getLayer() { 
    return m_node.getLayer(); 
}

bool GameObject::isDead() { 
    return m_isDead; 
}


template <class CompType>
CompType *GameObject::get() {
  return get_(tag<CompType>{});
}


template <class F>
bool GameObject::dispatch(F &&f) {
  return dispatch_(
    std::forward<F>(f), 
    typename params<std::decay_t<F>>::type{}
  );
}

template <class F, class... Params>
bool GameObject::dispatch_(F &&f, tag<Params...>) {

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