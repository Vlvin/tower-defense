#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <unistd.h>

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
#include "raylib.h"

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

    // std::vector<std::shared_ptr<IGameObject>> objects;

    double lastSpawned = GetTime() - 1, lastFrame = GetTime(), delta, tFPS = 60, tDelta = 1000/tFPS;
    bool draw = true;
    Picture pic = Picture((std::string("level/") + std::string(level_name) + std::string("/tilemap-32.png")).c_str());
    Tiler tiler = Tiler(pic, 32);

    // Vector2 cameraMin{
    //     Window::getInstance()->getSize().x*0.5f/SCALE, 
    //     Window::getInstance()->getSize().y*0.5f/SCALE
    // };
    // Vector2 cameraMax{
    //     map.getSize().x - cameraMin.x, 
    //     map.getSize().y - cameraMin.y
    // };

    // Vector2 camera = {Window::getInstance()->getSize().x*0.5f/SCALE, Window::getInstance()->getSize().y*0.5f/SCALE};

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
        if (IsKeyPressed(KEY_ENTER)) draw = !draw;
        if (GetTime() - lastSpawned > 1.f) {
            startUnit = map.getAny(Tile::START);
            std::shared_ptr<Creep> temp(
                        new Creep( scenes[index],
                            {startUnit.position.x, startUnit.position.y + 0.5f}, 
                            (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)),
                            5.f,
                            8,
                            (std::string("level/") + std::string(level_name) + std::string("/Zombie.png")).c_str()
                        )
                );
            temp->setColor(RED);
            scenes[index].add(temp);
            Path::cleanUp();
            lastSpawned = GetTime();
        } 
        // lastSpawned = GetTime();


        index += IsKeyDown(KEY_O) - IsKeyDown(KEY_I);
        index = std::min( std::max(index, 0), (int)scenes.size() - 1);

        Player::getInstance()->update(delta);
        scenes[index].update(delta);
        Vector2 size{1.f*pic.getTexture().width, 1.f*pic.getTexture().height};
        BeginDrawing();
            ClearBackground(BLACK);
            map.draw(scale, camera);
            if (draw) tiler.drawMap(map, scale, camera);
            scenes[index].draw();
        EndDrawing();

    
        // BeginDrawing();
        //     ClearBackground(BLACK);
        //     map.draw(SCALE);
        //     ((new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)))->draw(SCALE);
        //     for (int i = 0; i < map.getSize().y; i++)
        //         for (int j = 0; j < map.getSize().x; j++)
        //             DrawText(map[i][j].cost < 10 ? to_string(map[i][j].cost).c_str() : "inf", j*SCALE, i*SCALE, 17, BLACK);
        // EndDrawing();
        // Path::cleanUp();
    }
    Creep::cleanUp();
    Path::cleanUp();
    return 0;
}