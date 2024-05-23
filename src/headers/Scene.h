#pragma once

#include "stddef.h"
#include <list>
#include <vector>
#include <memory>

class IGameObject;

class Scene {
protected:
    std::list<std::shared_ptr<IGameObject>> objects;
public:
    void update(float deltaTime);
    void draw();
    void add(std::shared_ptr<IGameObject> object);
    auto begin() -> decltype(objects.begin()) ;
    auto end() -> decltype(objects.end()) ;
    // std::shared_ptr<IGameObject> get(size_t index);
    int size();
    ~Scene();
};