#pragma once
#include <raylib.h>
#include <cstdint> 

class Scene;

class Node {
protected:
    Scene &parent;
    uint32_t layer;
public:
    Node(Scene& parent, uint32_t layer = 1);
    virtual bool isUpdatable();
    uint32_t getDrawLayer();
    void setDrawLayer(uint32_t layer);
    virtual void update(float deltaTime) = 0;
    virtual void draw(float scale, Vector2 camera) = 0;
};