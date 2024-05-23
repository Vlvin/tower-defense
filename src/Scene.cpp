#include "Scene.h"

#include "IGameObject.h"
#include "Player.h"

void Scene::draw() {
    Vector2 camera = Player::getInstance()->getCamera();
    float scale = Player::getInstance()->getScale();
    
    for (std::shared_ptr<IGameObject> object : objects) 
        object->draw(scale, camera);

}

void Scene::update(float deltaTime) {
    for (std::shared_ptr<IGameObject> object : objects) 
        object->update(deltaTime);

    for (auto li = objects.begin(); li != objects.end(); li++) {
        auto object = (*li);
        if (object->getIsDead()) {
            *li = objects.back();
            objects.pop_back();
            li--;
        }
    }

}

void Scene::add(std::shared_ptr<IGameObject> object) {
    objects.push_back(object);
}

auto Scene::begin() -> decltype(objects.begin()) {
    return objects.begin();
}

auto Scene::end() -> decltype(objects.end()) {
    return objects.end();
}

// std::shared_ptr<IGameObject> Scene::get(size_t index) {
//     return objects.at(index);
// }

int Scene::size() {
    return objects.size();
}

Scene::~Scene() {
    objects.clear();
}