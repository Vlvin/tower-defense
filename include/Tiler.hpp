#pragma once
#include <raylib.h>
#include <array>

class Map;

class Tiler {
public:
  Tiler(const char* filename);

  void drawMap(Map& map);
protected:
  Texture2D getTile(Map& map, int x, int y);
  std::array<Texture2D, 14> m_tiles;
};