#pragma once
#include <raylib.h>
#include <array>

class Map;
class CameraObject;

class Tiler {
public:
  Tiler(const char* filename);

  void drawMap(Map& map, CameraObject& camera);
protected:
  Texture2D getTile(Map& map, int x, int y);
  std::array<Texture2D, 14> m_tiles;
};