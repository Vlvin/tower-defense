#include <GameObjects/Map.hpp>
#include <Tiler.hpp>
#include <LayerValues.hpp>

#include <Game.hpp>


Tiler::Tiler(const char* filename) {
  auto image = LoadImage(filename);
  if (!image.data) {
    std::cerr << "Failed to load " << filename << '\n';
    return;
  }
  // format of texture is one column
  Vector2 tileSize{
    (float)image.width,
    (float)floor(image.height / 14)
  };
  for (char i = 0; i < 14; i++) {
    Image temp = ImageFromImage(
      image,
      (Rectangle){
        0.f,
        i*tileSize.y,
        tileSize.x,
        tileSize.y
      }
    );
    m_tiles[i] = LoadTextureFromImage(temp);
    UnloadImage(temp);
  }
  UnloadImage(image);
}


void Tiler::drawMap(Map& map, CameraObject& camera) {
  float &scale = camera.getScale();
  Vector2 &camPos = camera.getPosition();
  for (const MapUnit& unit : map) {
    auto tile = getTile(map, unit.position.x, unit.position.y);  
    DrawTexturePro(
      tile,
      (Rectangle){0.f, 0.f, (float)tile.width, (float)tile.height},
      {(unit.position.x - camPos.x) * scale, (unit.position.y - camPos.y) * scale, scale, scale},    
      {0.5f * scale, 0.5f * scale}, // origin
      0.f, // rotation
      WHITE // color
    );
  }
}


Texture2D Tiler::getTile(Map& map, int x, int y) {

    int current = 4;
    if (map.getUnit(x, y).type == Tile::GRASS) {
        current = 9;
    } else if (map.getUnit(x, y).type == Tile::ROAD) {
        current = 4;
    }
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
    if (!(current&1)) return m_tiles[current];
    // writing one byte of sides
    u_char border = 0;
    // north
    if ((y > 0) && (map.getUnit(x, y).type != map.getUnit(x, y-1).type)) {
        border += 1;   
    } border <<= 1; // 1

    // south
    if ((y < map.getSize().y - 1) && (map.getUnit(x, y).type != map.getUnit(x, y+1).type)) {
        border += 1;   
    } border <<= 1; // 2

    if ((x > 0) && (map.getUnit(x, y).type != map.getUnit(x-1, y).type)) {
        border += 1;   
    } border <<= 1; // 3

    if ((x < map.getSize().x - 1) && (map.getUnit(x, y).type != map.getUnit(x+1, y).type)) {
        border += 1;   
    } border <<= 1; // 4

    if ((y > 0) && (x > 0) && (map.getUnit(x, y).type != map.getUnit(x-1, y-1).type)) {
        border += 1;
    } border <<= 1; // 5

    if ((y > 0) && (x < map.getSize().x - 1) && (map.getUnit(x, y).type != map.getUnit(x+1, y-1).type)) {
        border += 1;
    } border <<= 1; // 6

    if ((y < map.getSize().y - 1) && (x > 0) && (map.getUnit(x, y).type != map.getUnit(x-1, y+1).type)) {
        border += 1;
    } border <<= 1; // 7

    if ((y < map.getSize().y - 1) && (x < map.getSize().x - 1) && (map.getUnit(x, y).type != map.getUnit(x+1, y+1).type)) {
        border += 1;
    } // border <<= 1; // 8 do not need to shift


    // reading byte of safety border memory
    // more concrete ways i think these are double-border corners (two neigbours and corner between them are different)
    // north
    // std::cout << "\niter: " << u_int32_t(border) << "i: ";
    if (((border >> 7)&1) && ((border >> 5)&1) && ((border >> 3)&1))
        return m_tiles[10];

    if (((border >> 7)&1) && ((border >> 4)&1) && ((border >> 2)&1))
        return m_tiles[12];
    // south
    if (((border >> 6)&1) && ((border >> 5)&1) && ((border >> 1)&1))
        return m_tiles[11];

    if (((border >> 6)&1) && ((border >> 4)&1) && (border&1))
        return m_tiles[13];

    // std::cout << u_int32_t(border) << "i: ";

    // lessmore concrete ways i think these are borders (neighbour is different)
    // north
    if (((border >> 7)&1))
        return m_tiles[5];

    // south
    if (((border >> 6)&1))
        return m_tiles[3];

    // east
    if (((border >> 5)&1))
        return m_tiles[7];

    // west
    if (((border >> 4)&1))
        return m_tiles[1];

    // std::cout << u_int32_t(border) << "i: ";
    // moreless concrete ways i think these are zero-border corners (only corner is different)
    // north-west
    if (((border >> 3)&1))
        return m_tiles[8];

    // north-east
    if (((border >> 2)&1))
        return m_tiles[2];

    // south-west
    if (((border >> 1)&1))
        return m_tiles[6];

    // south-east
    if ((border&1))
        return m_tiles[0];

    return m_tiles[current];
}
