#pragma once
#include <raylib.h>
#include <memory>
#include "IGameObject.h"

class Map;
class Window;

class Player {
private:
    static std::shared_ptr<Player> player;
    Player(Map *map);
protected:
    int money;
    float scale;
    Map& map;
    Vector2 camera, cameraMax, cameraMin;
public:
    static std::shared_ptr<Player> getInstance(Map* map = nullptr);
    void update(float deltaTime);
    Vector2 getCamera();
    float getScale();
};