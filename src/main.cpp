#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "Map.h"
#include "PathFinder.h"
#include "Window.h"
#include "Creep.h"
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

    Window win(SCALE*width, SCALE*height, "PathFinder");

    MapUnit startUnit = map.getAny(Tile::START);
    if (!startUnit.cost) 
        startUnit = map[1][1];

    Path* first = (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH));

    Path* temp = first;

    std::vector<Creep> creeps;

    double lastSpawned = GetTime() - 1, lastFrame = GetTime(), delta, tFPS = 60, tDelta = 1000/tFPS;
    while (!WindowShouldClose()) {

        delta = (GetTime() - lastFrame) * 1000.f;
        lastFrame = GetTime();
        if (delta < tDelta) {
            usleep((tDelta - delta)*1000);
        }

        if (GetTime() - lastSpawned > 0.1f) {
            startUnit = map.getAny(Tile::START);
            creeps.push_back(
                Creep(
                    {startUnit.position.x - 1, startUnit.position.y}, 
                    (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(&map, map.getAny(Tile::FINISH)),
                    5.f
                )
            );
            Path::cleanUp();
            for (int i = 0; i < creeps.size() && creeps.size() > 0; i++) {
                if (creeps[i].isAtEnd()) {
                    creeps[i] = creeps.back();
                    creeps.pop_back();
                }
            }
            lastSpawned = GetTime();
        } 

        for (int i = 0; i < creeps.size(); i++)
            creeps[i].update(delta);
        

        BeginDrawing();
            ClearBackground(BLACK);
            map.draw(SCALE);
            for (int i = 0; i < creeps.size(); i++)
                creeps[i].draw(SCALE);
        EndDrawing();
    }
    
    Path::cleanUp();
    return 0;
}