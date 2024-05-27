#include "Scene.h"
#include <iostream>
#include "IGameObject.h"
#include "Player.h"

void Scene::draw() {
    Vector2 camera = Player::getInstance()->getCamera();
    float scale = Player::getInstance()->getScale();
    
    for (std::shared_ptr<Node> object : objects) 
        object->draw(scale, camera);

}

void Scene::update(float deltaTime) {
    for (std::shared_ptr<Node> object : objects) 
        if (object->isUpdatable())
            object->update(deltaTime);

    objects.remove_if([](std::shared_ptr<Node> object) 
    { 
        if (!object->isUpdatable()) return false; 

        return std::dynamic_pointer_cast
            <IGameObject>(object)->getIsDead();
    });
}

void Scene::add(std::shared_ptr<Node> object) {
    objects.push_back(object);
    objects.sort([](std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        return left->getDrawLayer() > right->getDrawLayer();
    });
}

auto Scene::begin() -> decltype(objects.begin()) {
    return objects.begin();
}

auto Scene::end() -> decltype(objects.end()) {
    return objects.end();
}

int Scene::size() {
    return objects.size();
}

Scene::~Scene() {
    objects.clear();
}