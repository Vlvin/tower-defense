#pragma once
#include <raylib.h>
#include "Node.h"

class Map;
class Picture;
/**
 * you can check texture example at level/demo/tilemap-32.png
 * size of tile and texture are changeable but other is not 
*/
class Tiler : public Node {
protected:
    Texture2D *tiles;
    Map& map;
    int sizeOfTile;
public:
    Texture2D getTile(Map &map, int x, int y);
    Tiler(Scene& parent, Picture &tileTexture, Map &map, int sizeOfTile);
    void drawMap(Map& map, float scale, Vector2 camera);
    virtual void draw(float scale, Vector2 camera);
    virtual void update(float deltaTime);
    ~Tiler();
};