#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>

#include "Map.h"
#include "PathFinder.h"
#include "Window.h"
#include "Creep.h"
#include "Bullet.h"
#include "Tiler.h"
#include "IGameObject.h"
#include "Picture.h"
#include "Tourel.h"
#include "raylib.h"

#define SCALE 20.f

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

    Window::getInstance(SCALE*width, SCALE*height, "PathFinder");

    MapUnit startUnit = map.getAny(Tile::START);
    if (!startUnit.cost) 
        startUnit = map[1][1];

    Path* first = (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH));

    Path* temp = first;

    // new Tourel({20.5f, 3.5f, 1.f, 1.f}, 20.f, .1f);
    // new Tourel({17.5f, 16.5f, 1.f, 1.f}, 20.f, .1f);
    new Tourel({20.5f, 9.5f, 1.f, 1.f}, 20.f, .1f);

    // std::vector<std::shared_ptr<IGameObject>> objects;

    double lastSpawned = GetTime() - 1, lastFrame = GetTime(), delta, tFPS = 60, tDelta = 1000/tFPS;
    bool draw = true;
    Picture pic = Picture((std::string("level/") + std::string(level_name) + std::string("/tilemap-32.png")).c_str());
    Tiler tiler = Tiler(pic, 32);
    while (!WindowShouldClose()) {

        delta = (GetTime() - lastFrame) * 1000.f;
        lastFrame = GetTime();
        if (delta < tDelta) {
            usleep((tDelta - delta)*1000);
        }
        if (IsKeyPressed(KEY_ENTER)) draw = !draw;
        if (GetTime() - lastSpawned > 1.f) {
            startUnit = map.getAny(Tile::START);
            new Creep(
                        {startUnit.position.x, startUnit.position.y + 0.5f}, 
                        (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)),
                        5.f,
                        8,
                        (std::string("level/") + std::string(level_name) + std::string("/Zombie.png")).c_str()
                    );
            Path::cleanUp();
            Creep::clearAtEnd();
            lastSpawned = GetTime();
        } 
        // lastSpawned = GetTime();


        Creep::updateAll(delta);
        Tourel::updateAll(delta);
        Bullet::updateAll(delta);
        Vector2 size{1.f*pic.getTexture().width, 1.f*pic.getTexture().height};
        BeginDrawing();
            ClearBackground(BLACK);
            map.draw(SCALE);
            if (draw) tiler.drawMap(map, SCALE);
            Creep::drawAll(SCALE);
            Bullet::drawAll(SCALE);
            Tourel::drawAll(SCALE);
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
    Tourel::cleanUp();
    return 0;
}