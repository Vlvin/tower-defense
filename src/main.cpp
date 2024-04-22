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
#include "IGameObject.h"
#include "Tourel.h"
#include "raylib.h"

#define SCALE 20

/**
 * Pathfinder logic
 * 1. Add start node in vector
 * 2. Sort nodes by sum(cost to prev=nullptr)
 * 3. replace top_node by top_node->getNeighbours()
 * 4. repeat until top_node != goal_node
*/

using namespace std;

int main() {
    // // image parsing

    Map map = Map::loadFromFile("map.ppm");
    int width = map.getSize().x;
    int height = map.getSize().y;

    Window::getInstance(SCALE*width, SCALE*height, "PathFinder");

    MapUnit startUnit = map.getAny(Tile::START);
    if (!startUnit.cost) 
        startUnit = map[1][1];

    Path* first = (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH));

    Path* temp = first;

    IGameObject* tourel = new Tourel({18.f, 10.f, 1.f, 1.f}, 20.f, .1f);

    // std::vector<std::shared_ptr<IGameObject>> objects;

    double lastSpawned = GetTime() - 1, lastFrame = GetTime(), delta, tFPS = 60, tDelta = 1000/tFPS;
    while (!WindowShouldClose()) {

        delta = (GetTime() - lastFrame) * 1000.f;
        lastFrame = GetTime();
        if (delta < tDelta) {
            usleep((tDelta - delta)*1000);
        }

        if (GetTime() - lastSpawned > 1.f) {
            startUnit = map.getAny(Tile::START);
            new Creep(
                        {startUnit.position.x, startUnit.position.y + 0.5f}, 
                        (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)),
                        5.f
                    );
            Path::cleanUp();
            Creep::clearAtEnd();
            lastSpawned = GetTime();
        } 
        // lastSpawned = GetTime();


        Creep::updateAll(delta);
        tourel->update(delta);
        Bullet::updateAll(delta);
        
        BeginDrawing();
            ClearBackground(BLACK);
            map.draw(SCALE);
            Creep::drawAll(SCALE);
            tourel->draw(SCALE);
            Bullet::drawAll(SCALE);
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