#pragma once

#include "stddef.h"
#include <list>
#include <vector>
#include <memory>

class Node;

class Scene {
protected:
    std::list<std::shared_ptr<Node>> objects;
public:
    void update(float deltaTime);
    void draw();
    void add(std::shared_ptr<Node> object);
    auto begin() -> decltype(objects.begin()) ;
    auto end() -> decltype(objects.end()) ;
    // std::shared_ptr<IGameObject> get(size_t index);
    int size();
    ~Scene();
};