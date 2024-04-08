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

    MapUnit start = map.getAny(Tile::START);
    if (!start.cost) 
        start = map[1][1];

    
    vector<Path*> paths = {new Path(start.position, start.cost)};
    Path* current = paths.at(0);
    printf("main: start_node at %d:%d has prev == %p\n", (int)(current->getPosition().x), (int)(current->getPosition().y), current->getPrevious());
    paths.pop_back();
    vector<Path*> temp = current->getNeighbours(&map);

    for (int i = 0; i < temp.size(); i++) {
        paths.push_back(temp.at(i));
    }
    while(!temp.empty()) 
        temp.pop_back();

    for (int i = 0; i < paths.size(); i++) {
        printf("main: Path at %p has prev == %p\n", paths.at(i), paths.at(i)->getPrevious());
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    DrawRectangle(j*SCALE, i*SCALE, SCALE, SCALE, map[i][j].color);
                }
            }
        EndDrawing();
    }
    Path::cleanUp();
    return 0;
}