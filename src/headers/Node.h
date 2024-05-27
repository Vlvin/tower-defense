#pragma once
#include <raylib.h>

class Scene;

class Node {
protected:
    Scene &parent;
public:
    Node(Scene& parent);
    virtual void update(float deltaTime) = 0;
    virtual bool isUpdatable();
    virtual void draw(float scale, Vector2 camera) = 0;
};