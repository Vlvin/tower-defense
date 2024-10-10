#include <GameObjects/GameObject.hpp>

GameObject::GameObject(uint8_t layer) 
    : m_node(layer), m_isDead(false)
{}

void GameObject::setLayer(uint8_t layer) {
    m_node.setLayer(layer);
}


uint8_t GameObject::getLayer() { 
    return m_node.getLayer(); 
}

bool GameObject::isDead() { 
    return m_isDead; 
}
