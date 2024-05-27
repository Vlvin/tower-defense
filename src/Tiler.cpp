#include "Tiler.h"

#include "Map.h"
#include "Window.h"
#include "Picture.h"

Tiler::Tiler(Scene& parent, Picture &tileTexture, Map &map, int sizeOfTile)
: Node(parent), map(map)
{
    if (tileTexture.getImage().height != sizeOfTile*14) {
        fprintf(stderr, "Not equal tiles size\nexpected %d but %d found instead\n", sizeOfTile*14, tileTexture.getTexture().height);
        return;
    }
    tiles = new Texture2D[14];
    this->sizeOfTile = sizeOfTile;
    for (char i = 0; i < 14; i++) {
        Image temp = ImageFromImage(
            tileTexture.getImage(), 
            (Rectangle){
                0.f,
                i*sizeOfTile,
                32.f,
                32.f
            }
        );
        tiles[i] = LoadTextureFromImage(temp);
        UnloadImage(temp);
    }
}

Tiler::~Tiler() {
    delete[] tiles;
}

Texture2D Tiler::getTile(Map& map, int x, int y) {

    int current = 4;
    if (map[y][x].type == Tile::GRASS) {
        current = 9;
    } else if (map[y][x].type == Tile::ROAD) {
        current = 4;
    } else return Texture2D{0, 0, 0, 0, 0};
    /** map (number is number of shifts to get value)
     * 7 - north
     * 6 - south
     * 5 - west
     * 4 - east
     * 3 - north-west
     * 2 - north-east
     * 1 - south-west
     * 0 - south-east
    */
    if (!(current&1)) return tiles[current];
    // writing one byte of sides
    u_char border = 0;
    // north
    if ((y > 0) && (map[y][x].type != map[y-1][x].type)) {
        border += 1;   
    } border <<= 1; // 1

    // south
    if ((y < map.getSize().y - 1) && (map[y][x].type != map[y+1][x].type)) {
        border += 1;   
    } border <<= 1; // 2

    if ((x > 0) && (map[y][x].type != map[y][x-1].type)) {
        border += 1;   
    } border <<= 1; // 3

    if ((x < map.getSize().x - 1) && (map[y][x].type != map[y][x+1].type)) {
        border += 1;   
    } border <<= 1; // 4

    if ((y > 0) && (x > 0) && (map[y][x].type != map[y-1][x-1].type)) {
        border += 1;
    } border <<= 1; // 5

    if ((y > 0) && (x < map.getSize().x - 1) && (map[y][x].type != map[y-1][x+1].type)) {
        border += 1;
    } border <<= 1; // 6

    if ((y < map.getSize().y - 1) && (x > 0) && (map[y][x].type != map[y+1][x-1].type)) {
        border += 1;
    } border <<= 1; // 7

    if ((y < map.getSize().y - 1) && (x < map.getSize().x - 1) && (map[y][x].type != map[y+1][x+1].type)) {
        border += 1;
    } // border <<= 1; // 8 do not need to shift


    // reading byte of safety border memory
    // more concrete ways i think these are double-border corners (two neigbours and corner between them are different)
    // north
    // std::cout << "\niter: " << u_int32_t(border) << "i: ";
    if (((border >> 7)&1) && ((border >> 5)&1) && ((border >> 3)&1))
        return tiles[10];

    if (((border >> 7)&1) && ((border >> 4)&1) && ((border >> 2)&1))
        return tiles[12];
    // south
    if (((border >> 6)&1) && ((border >> 5)&1) && ((border >> 1)&1))
        return tiles[11];

    if (((border >> 6)&1) && ((border >> 4)&1) && (border&1))
        return tiles[13];

    // std::cout << u_int32_t(border) << "i: ";

    // lessmore concrete ways i think these are borders (neighbour is different)
    // north
    if (((border >> 7)&1))
        return tiles[5];

    // south
    if (((border >> 6)&1))
        return tiles[3];

    // east
    if (((border >> 5)&1))
        return tiles[7];

    // west
    if (((border >> 4)&1))
        return tiles[1];

    // std::cout << u_int32_t(border) << "i: ";
    // moreless concrete ways i think these are zero-border corners (only corner is different)
    // north-west
    if (((border >> 3)&1))
        return tiles[8];

    // north-east
    if (((border >> 2)&1))
        return tiles[2];

    // south-west
    if (((border >> 1)&1))
        return tiles[6];

    // south-east
    if ((border&1))
        return tiles[0];

    return tiles[current];
}

void Tiler::drawMap(Map& map, float scale, Vector2 camera) {
    map.draw(scale, camera);
    for (int i = 0; i < map.getSize().y; i++)
        for (int j = 0; j < map.getSize().x; j++) {
            Texture2D temp = getTile(map, j, i);
            if (temp.width)
                DrawTexturePro(
                    temp, 
                    (Rectangle){0, 0, sizeOfTile, sizeOfTile}, 
                    (Rectangle){
                        (j - camera.x)*scale + Window::getInstance()->getSize().x * 0.5f, 
                        (i - camera.y)*scale + Window::getInstance()->getSize().y * 0.5f, 
                        scale, scale}, {0.,0.}, 0., WHITE);
        }
}

void Tiler::update(float deltaTime) {}

void Tiler::draw(float scale, Vector2 camera) {
    map.draw(scale, camera);
    for (int i = 0; i < map.getSize().y; i++)
        for (int j = 0; j < map.getSize().x; j++) {
            Texture2D temp = getTile(map, j, i);
            if (temp.width)
                DrawTexturePro(
                    temp, 
                    (Rectangle){0, 0, sizeOfTile, sizeOfTile}, 
                    (Rectangle){
                        (j - camera.x)*scale + Window::getInstance()->getSize().x * 0.5f, 
                        (i - camera.y)*scale + Window::getInstance()->getSize().y * 0.5f, 
                        scale, scale}, {0.,0.}, 0., WHITE);
        }
}