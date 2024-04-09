#include <iostream>
#include <string>
#include <vector>

#include "Map.h"
#include "PathFinder.h"
#include "Window.h"
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

    while (!WindowShouldClose()) {
        BeginDrawing();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    DrawRectangle(j*SCALE, i*SCALE, SCALE, SCALE, map[i][j].color);
                }
            }
            for (temp = first; temp != nullptr; temp = temp->getNext()) {
                Vector2 pos = temp->getPosition();
                DrawRectangle(pos.x*SCALE, pos.y*SCALE, SCALE, SCALE, PURPLE);
            }
        EndDrawing();
    }
    
    Path::cleanUp();
    return 0;
}