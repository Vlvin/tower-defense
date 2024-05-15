#pragma once
#include <raylib.h>

class Map;
class Picture;
/**
 * you can check texture example at level/demo/tilemap-32.png
 * size of tile and texture are changeable but other is not 
*/
class Tiler {
protected:
    Texture2D *tiles;
    int sizeOfTile;
public:
    Texture2D getTile(Map &map, int x, int y);
    Tiler(Picture &tileTexture, int sizeOfTile);
    void drawMap(Map& map, float scale, Vector2 camera);
    ~Tiler();
};