#include <GameObjects/Map.hpp>
#include <GameObjects/Creep.hpp>
#include <GameObjects/Spawner.hpp>
#include <GameObjects/Placeholder.hpp>
#include <InputHandler.hpp>
#include <Tiler.hpp>
#include <ColorTools.hpp>
#include <SceneManager.hpp>
#include <PathNode.hpp>
#include <Game.hpp>
#include <LayerValues.hpp>

#include <string>
#include <map>
#include <cmath>


WrongUnitRequest::WrongUnitRequest(const char* message) 
  : m_message(std::string(message).c_str())
{}

const char* WrongUnitRequest::what() const noexcept {
  return m_message;
}


using _Map = std::shared_ptr<Map>;
using _Object = std::shared_ptr<GameObject>;
Map::LevelInfo Map::loadLevelFromFile(const char *filename, InputHandler& input)
{
  // fileData
  char *c_rawData = LoadFileText(filename);
  std::string rawMapData = c_rawData;
  UnloadFileText(c_rawData);

  int width, height;
  int previous_pos, channels = 3, nowChannel = 0, actual_size = 0;
  std::vector<uint8_t> colorByte;

  std::vector<Color> mapImage;
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
        mapImage.reserve(width*height);
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
              mapImage[actual_size].r 
              = mapImage[actual_size].g 
              = mapImage[actual_size].b = colorByte[0];
              mapImage[actual_size].a = 255;
              break;
            case 3:
              mapImage[actual_size].r = colorByte[0];
              mapImage[actual_size].g = colorByte[1];
              mapImage[actual_size].b = colorByte[2];
              mapImage[actual_size].a = 255;
              break;
            case 4:
              mapImage[actual_size].r = colorByte[0];
              mapImage[actual_size].g = colorByte[1];
              mapImage[actual_size].b = colorByte[2];
              mapImage[actual_size].a = colorByte[3];
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
  auto map = std::make_shared<Map>(mapImage, width, height);
  std::vector<_Object> objects;
  for (int i = 0; i < map->getSize().y; i++) {
    for (int j = 0; j < map->getSize().x; j++) {
      switch (map->getUnit(j, i).type) {
        case Tile::PLACEHOLDER:
          objects.emplace_back(
            new PlaceHolder(
              input,
              (Vector2){(float)j, (float)i}
            )
          );
          break;
        case Tile::START: {
          #define SPAWN_INTERVAL 0.5
          auto goal = map->getUnit(0, 0);
          auto spawnObject = std::shared_ptr<ICloneable>(
            new Creep(
              (Rectangle){ j*1.f, i*1.f, 1.f, 1.f },
              *map,
              map->getUnit(j, i)
            )
          );
          objects.push_back(
            std::dynamic_pointer_cast<GameObject>(std::make_shared<Spawner>(
              SPAWN_INTERVAL, 
              1,
              spawnObject
            )
          ));
        }

      }
    }
  }
  return (LevelInfo){map, objects};
}


Map::Map(std::vector<Color> &data, uint width, uint height) 
  : GameObject(MAP_DRAW_LAYER)
{
  m_tiler = nullptr;
  m_lastSpawned = GetTime() - 99;
  m_tiler = nullptr;
  m_width = width;
  m_height = height;
  m_data.reserve(m_width*m_height);
  std::map<Tile, int> tile_costs = {
    {Tile::ROAD, 1},
    {Tile::START, 1},
    {Tile::FINISH, 1},
    {Tile::PLACEHOLDER, INT32_MAX},
    {Tile::GRASS, INT32_MAX}
  };

  for (int i = 0; i < width*height; i++) {
    int cost = 1;
    Tile current;
    // get current
    if (CT::colorCompare(data[i], Color{255, 255, 0, 255})) {
        current = Tile::ROAD;
    } else if (CT::colorCompare(data[i], Color{255, 255, 255, 255})) {
        current = Tile::PLACEHOLDER;
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
      case PLACEHOLDER:
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


void Map::attachTiler(std::shared_ptr<Tiler> tiler) {
  m_tiler = tiler;
}


void Map::update(double deltaTime, CameraObject& camera) {
  // spawnCreeps();
}

void Map::draw(CameraObject& camera) {
  Vector2 winSize = (Vector2)
  {
    (float)GetScreenWidth(),
    (float)GetScreenHeight()
  };
  float &scale = camera.getScale();
  Vector2 &camPos = camera.getPosition();

  for (int i = 0; i < m_height; i++)
    for (int j = 0; j < m_width; j++)
    {
      DrawRectanglePro(
        {(j-camPos.x)*scale, (i-camPos.y)*scale, scale, scale}, 
        {scale*0.5f, scale*0.5f},
        0.0f,
        m_data[i*m_width+j].color);
    }
  if (m_tiler)
    m_tiler->drawMap(*this, camera);
}

MapUnit Map::getUnit(uint x, uint y) {

  return m_data.at(x+y*m_width);
}

Vector2 Map::getSize() {
  return (Vector2)
    {
      (float)m_width,
      (float)m_height
    };
}

std::vector<MapUnit>::iterator Map::begin() {
  return m_data.begin();
}

std::vector<MapUnit>::iterator Map::end() {
  return m_data.end();
}


MapUnit Map::getRandomUnit(Tile type) {
  srand(GetTime());
  switch (type) {
    case Tile::START: {
      int index = rand() % m_spawns.size();
      Vector2 point = m_spawns[index]->position;
      return getUnit(point.x, point.y);
    }
    case Tile::FINISH:{
      int index = rand() % m_goals.size();
      Vector2 point = m_goals[index]->position;
      return getUnit(point.x, point.y);
    }
    case Tile::PLACEHOLDER:{
      int index = rand() % m_placeholders.size();
      Vector2 point = m_placeholders[index]->position;
      return getUnit(point.x, point.y);
    }
    default:
      throw WrongUnitRequest("Wrong Tile Type requested");
  }
}