#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <unistd.h>
#include "raylib.h"

#include "Map.h"
#include "Scene.h"
#include "PathFinder.h"
#include "Player.h"
#include "Window.h"
#include "Creep.h"
#include "Bullet.h"
#include "Tiler.h"
#include "IGameObject.h"
#include "Picture.h"
#include "Tourel.h"

/**
 * Pathfinder logic
 * 1. Add start node in vector
 * 2. Sort nodes by sum(cost to prev=nullptr)
 * 3. replace top_node by top_node->getNeighbours()
 * 4. repeat until top_node != goal_node
*/

using namespace std;

int main(int argc, char** argv) {
    // // image parsing
    char *level_name = "demo";
    if (argc >= 2) {
        level_name = argv[argc-1];
    }

    Map map = Map::loadFromFile((std::string("level/") + std::string(level_name) + std::string("/map.ppm")).c_str());
    int width = map.getSize().x;
    int height = map.getSize().y;

    Window::getInstance(640, 480, "PathFinder");

    MapUnit startUnit = map.getAny(Tile::START);
    if (!startUnit.cost) 
        startUnit = map[1][1];

    Path* first = (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH));
    Path* temp = first;

    int index = 0;
    std::vector<Scene> scenes(10);

    scenes[0].add(std::make_shared<Tourel>(scenes[0], Rectangle{7.f, 11.f, 1.f, 1.f}, 100.f, .01f, 2));
    double lastSpawned = GetTime() - 1, lastFrame = GetTime(), delta, tFPS = 60, tDelta = 1000/tFPS;
    Picture pic = Picture((std::string("level/") + std::string(level_name) + std::string("/tilemap-32.png")).c_str());
    scenes[index].add(std::make_shared<Tiler>(scenes[index], pic, map, 32, 3));

    Player::getInstance(&map);

    float scale;
    Vector2 camera;

    while (!WindowShouldClose()) {

        scale = Player::getInstance()->getScale();
        camera = Player::getInstance()->getCamera();

        delta = (GetTime() - lastFrame) * 1000.f;
        lastFrame = GetTime();
        if (delta < tDelta) {
            usleep((tDelta - delta)*1000);
        }
        
        if (GetTime() - lastSpawned > 1.f) {
            startUnit = map.getAny(Tile::START);
            std::shared_ptr<Creep> temp(
                        new Creep( scenes[index],
                            {startUnit.position.x, startUnit.position.y + 0.5f}, 
                            (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)),
                            5.f,
                            8,
                            (std::string("level/") + std::string(level_name) + std::string("/Zombie.png")).c_str(),
                            3
                        )
                );
            temp->setColor(RED);
            scenes[index].add(temp);
            Path::cleanUp();
            lastSpawned = GetTime();
        }


        index += IsKeyPressed(KEY_O) - IsKeyPressed(KEY_I);
        index = std::min( std::max(index, 0), (int)scenes.size() - 1);

        Player::getInstance()->update(delta);
        scenes[index].update(delta);
        
        BeginDrawing();
            ClearBackground(BLACK);
            scenes[index].draw();
        EndDrawing();
    }
    Creep::cleanUp();
    Path::cleanUp();
    return 0;
}