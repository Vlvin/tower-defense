#pragma once

#include "stddef.h"
#include <list>
#include <vector>
#include <memory>

class Node;
class Map;

class Scene {
protected:
    std::unique_ptr<Map> map;
    std::list<std::shared_ptr<Node>> objects;
public:
    void update(float deltaTime);
    void draw();
    void add(std::shared_ptr<Node> object);
    void addMap(std::unique_ptr<Map> map);
    auto begin() -> decltype(objects.begin()) ;
    auto end() -> decltype(objects.end()) ;
    // std::shared_ptr<IGameObject> get(size_t index);
    int size();
    ~Scene();
};