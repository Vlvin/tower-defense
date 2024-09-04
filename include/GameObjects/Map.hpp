#pragma once
#include <vector>
#include <memory>

#include <GameObjects/IGameObject.hpp>
#include <limits>
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
    int cost;
    Tile type;
} MapUnit;

class Map : public IGameObject {
public:
  static std::shared_ptr<Map> loadFromFile(const char *filename);
  Map(std::vector<Color> &data, uint width, uint height);
  void attachTiler(std::shared_ptr<Tiler> tiler);

  MapUnit getUnit(uint x, uint y);
  Vector2 getSize();

  virtual void update(double deltaTime, CameraObject& camera);
  virtual void draw(CameraObject& camera);

  std::vector<MapUnit>::iterator begin();
  std::vector<MapUnit>::iterator end();
protected:
  void spawnCreeps();
protected:
  double m_lastSpawned;
  std::vector<MapUnit> m_data;
  std::vector<MapUnit*> m_placeholders, m_spawns, m_goals;
  std::shared_ptr<Tiler> m_tiler;
  uint m_width, m_height;
};