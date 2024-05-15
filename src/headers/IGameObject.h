#pragma once 
#include <raylib.h>
#include <list>
#include <memory>

class IGameObject {
    static std::list<IGameObject*> all;
    static std::list<IGameObject*> removals;
protected:
    Rectangle body;
    Texture2D texture;
    float angle;
    Color color;
public:
    IGameObject(Rectangle body, float angle);
    virtual bool isCollidable() = 0;
    virtual void update(float delta) = 0;
    virtual void draw(float scale, Vector2 camera);
    static void updateAll(float delta);
    static void drawAll(float scale, Vector2 camera);
    static void remove(IGameObject* object);
    static void cleanUp();
    static std::list<IGameObject*>::iterator begin();
    static std::list<IGameObject*>::iterator end();
    void setColor(Color color);
    Vector2 getPosition();
    float getAngle();
};