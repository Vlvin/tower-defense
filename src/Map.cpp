#include "Map.hpp"
#include "ColorTools.hpp"
#include "Creep.hpp"
#include "SceneManager.hpp"
#include "PathNode.hpp"

#include <string>
#include <map>
#include <cmath>


std::shared_ptr<Map> Map::loadFromFile(const char *filename)
{
  // fileData
  char *c_rawData = LoadFileText(filename);
  std::string rawMapData = c_rawData;
  UnloadFileText(c_rawData);

  int width, height;
  int previous_pos, channels = 3, nowChannel = 0, actual_size = 0;
  std::vector<uint8_t> colorByte;
  // Image im;
  std::vector<Color> map;
  char current;

  for (int i = 0; rawMapData[i] != '\0'; i++) {
    current = rawMapData[i];
    switch(current) {
      case '#':
        while(rawMapData[++i] != '\n');
        previous_pos = ++i;
        break;
      case ' ':
        width = stod(rawMapData.substr(previous_pos, i - previous_pos));
        previous_pos = ++i;
        while (rawMapData[++i] != '\n');
        height = stod(rawMapData.substr(previous_pos, i - previous_pos));
        while (rawMapData[++i] != '\n');
        previous_pos = ++i;
        map.reserve(width*height);
        break;
      case 'P':
        previous_pos = ++i;
        channels = stod(rawMapData.substr(previous_pos, ++i - previous_pos));
        colorByte.reserve(channels);
        while (rawMapData[++i] != '\n');
        previous_pos = ++i;
        break;
      case '\n':
        if (actual_size >= width*height) {
          previous_pos = i+1;
          break;
        }
        colorByte[nowChannel] = (int)stod(rawMapData.substr(previous_pos, i-previous_pos));
        if (++nowChannel >= channels) {
          switch(channels) {
            case 1:
              map[actual_size].r 
              = map[actual_size].g 
              = map[actual_size].b = colorByte[0];
              map[actual_size].a = 255;
              break;
            case 3:
              map[actual_size].r = colorByte[0];
              map[actual_size].g = colorByte[1];
              map[actual_size].b = colorByte[2];
              map[actual_size].a = 255;
              break;
            case 4:
              map[actual_size].r = colorByte[0];
              map[actual_size].g = colorByte[1];
              map[actual_size].b = colorByte[2];
              map[actual_size].a = colorByte[3];
              break;
          }
          actual_size+=1;
          nowChannel = 0;
        }
        previous_pos = i+1;
        break;
      default:
        break;
    }
  }
  colorByte.clear();
  return std::make_shared<Map>(map, width, height);
}


Map::Map(std::vector<Color> &data, uint width, uint height) 
  : IGameObject(MAP_DRAW_LAYER)
{
  m_tiler = nullptr;
  m_width = width;
  m_height = height;
  m_data.reserve(m_width*m_height);
  std::map<Tile, uint> tile_costs = {
    {Tile::ROAD, uint(1)},
    {Tile::START, uint(1)},
    {Tile::FINISH, uint(1)},
    {Tile::TOUREL, 2147000000},
    {Tile::GRASS, 2147000000}
  };

  for (int i = 0; i < width*height; i++) {
    uint32_t cost = 1;
    Tile current;
    // get current
    if (CT::colorCompare(data[i], Color{255, 255, 0, 255})) {
        current = Tile::ROAD;
    } else if (CT::colorCompare(data[i], Color{255, 255, 255, 255})) {
        current = Tile::TOUREL;
    } else if (CT::colorCompare(data[i], Color{0, 0, 255, 255})) {
        current = Tile::START;
    } else if (CT::colorCompare(data[i], Color{255, 0, 0, 255})) {
        current = Tile::FINISH;
    } else {
        current = Tile::GRASS;
    }
    cost = tile_costs.find(current)->second; // getting enum value
    m_data.push_back(
        MapUnit
        {
          data[i], 
          (Vector2)
          {
            (float)(i%width),
            (float)(i/width)
          },
          cost,
          current
        }
      );
    
    // fill concrete vectors with with references
    switch (current) {
      case TOUREL:
        m_placeholders.push_back(&m_data[i]);
        break;
      case START:
        m_spawns.push_back(&m_data[i]);
        break;
      case FINISH:
        m_goals.push_back(&m_data[i]);
        break;
    }
  }
}

void Map::update(double deltaTime) {
  spawnCreeps();
}
void Map::draw() {
  Vector2 winSize = (Vector2)
  {
    GetScreenWidth(),
    GetScreenHeight()
  };
  uint scale = 10;
  for (int i = 0; i < m_height; i++)
    for (int j = 0; j < m_width; j++)
    {
      DrawRectangle(j*scale, i*scale, scale, scale, m_data[i*m_width+j].color);
    }

}

void Map::spawnCreeps() {
  srand(GetTime());
  int index = rand() % m_spawns.size();

  Vector2 position = m_spawns.at(index)->position;
  srand(GetTime());
  index = rand() % m_goals.size();

  Vector2 goal = m_goals.at(index)->position;
  
  auto creep = std::make_shared<Creep>(
    (Rectangle){ position.x, position.y, 20.f, 20.f },
    PathNode(getUnit(int(position.x), int(position.y))).findPath(this, goal)
  );
  
  SceneManager::Back()->pushObject(creep);
}

MapUnit Map::getUnit(uint x, uint y) {
  return m_data.at(y*m_width+x);
}

Vector2 Map::getSize() {
  return (Vector2)
        {
          (float)m_width,
          (float)m_height
        };
}