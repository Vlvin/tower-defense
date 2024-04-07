#include <iostream>
#include <string>

#include "Map.h"
#include "PathFinder.h"
#include "Window.h"
#include "raylib.h"


using namespace std;

int main() {
    const char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* lower = "abcdefghijklmnopqrstuvwxyz";
    // // image parsing

    Map map = Map::load("map.ppm");
    int width = map.getSize().x;
    int height = map.getSize().y;

    Window win(640, 480, "Hello World!");
    while (!WindowShouldClose()) {
        BeginDrawing();
            DrawText(upper, 10, 240, 20, GREEN);
            for (int i = 0; upper[i] != '\0'; i++)
                DrawRectangle(10+13*i, 260, 12, 20, WHITE);
            DrawText(lower, 10, 280, 20, GREEN);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    DrawRectangle(j*10, i*10, 10, 10, map[i][j]);
                }
            }
            for (int i = 0; lower[i] != '\0'; i++)
                DrawRectangle(10+10*i, 300, 9, 20, WHITE);
        EndDrawing();
    }
    return 0;
}