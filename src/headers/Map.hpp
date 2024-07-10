#pragma once
#include <vector>
#include <memory>

#include "IGameObject.hpp"

class Tiler;


typedef enum {
    GRASS,
    ROAD,
    TOUREL,
    START,
    FINISH
} Tile;


typedef struct {
    Color color;
    Vector2 position;
    uint32_t cost;
    Tile type;
} MapUnit;

class Map : public IGameObject {
public:
  static std::shared_ptr<Map> loadFromFile(const char *filename);
  Map(std::vector<Color> &data, uint width, uint height);
  void attachTiler(std::shared_ptr<Tiler> tiler);
  virtual void update(double deltaTime);
  virtual void draw();
private:
  void spawnCreeps();
  std::vector<MapUnit> m_data;
  std::vector<MapUnit&> m_placeholders, m_spawns, m_goals;
  std::shared_ptr<Tiler> m_tiler;
  uint m_width, m_height;
};