#include "Player.h"
#include <iostream>

#include "Window.h"
#include "Map.h"

std::shared_ptr<Player> Player::player(nullptr);

std::shared_ptr<Player> Player::getInstance(Map* map) {
    if (player) return player;
    if (!map) {
        std::cout << "First time Map cant be NULL\n";
        return nullptr;
    }
    player = std::shared_ptr<Player>(new Player(map));
    return player;
}

Player::Player(Map* map) : map(*map) {
    scale = 20.f;
    camera = {Window::getInstance()->getSize().x*0.5f/scale, Window::getInstance()->getSize().y*0.5f/scale};


    cameraMin = Vector2{
        Window::getInstance()->getSize().x*0.5f/scale, 
        Window::getInstance()->getSize().y*0.5f/scale
    };

    cameraMax = Vector2{
        map->getSize().x - cameraMin.x, 
        map->getSize().y - cameraMin.y
    };
}

void Player::update(float deltaTime) {
    cameraMin = Vector2{
        Window::getInstance()->getSize().x*0.5f/scale, 
        Window::getInstance()->getSize().y*0.5f/scale
    };

    cameraMax = Vector2{
        map.getSize().x - cameraMin.x, 
        map.getSize().y - cameraMin.y
    };
    if (IsKeyDown(KEY_W) && (camera.y > cameraMin.y)) camera.y -= 0.1;
    if (IsKeyDown(KEY_A) && (camera.x > cameraMin.x)) camera.x -= 0.1;
    if (IsKeyDown(KEY_S) && (camera.y < cameraMax.y)) camera.y += 0.1;
    if (IsKeyDown(KEY_D) && (camera.x < cameraMax.x)) camera.x += 0.1;
    if (IsKeyDown(KEY_UP) && (scale < 100.f)) {
        scale += 1;
    }
    if (IsKeyDown(KEY_DOWN) && (scale > 10.f)) {
        scale -= 1;
    } 
}

Vector2 Player::getCamera() {
    return camera;
}

float Player::getScale() {
    return scale;
}