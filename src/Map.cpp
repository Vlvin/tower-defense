#include "Map.h"
#include "File.h"
#include "Window.h"
#include "IGameObject.h"
#include "Creep.h"
#include "PathFinder.h"
#include "ColorTools.h"
#include <map>
#include <cmath>
#include <string>
#include <sys/time.h>
#include <malloc.h>

// Map type
Map::Map(Scene& parent, int width, int height, Color* data) : Node(parent, 4) {
    lastSpawned = GetTime();
    this->width = width;
    this->height = height;
    this->data = (MapUnit*)malloc(width*height*sizeof(MapUnit));
    std::map<Tile_t, uint32_t> tile_costs = {
        {Tile::ROAD, uint32_t(1)},
        {Tile::START, uint32_t(1)},
        {Tile::FINISH, uint32_t(1)},
        {Tile::TOUREL, 2147000000},
        {Tile::GRASS, 2147000000}
    };
    for (int i = 0; i < width*height; i++) {
        uint32_t cost = 1;
        Tile_t current;
        if (CT::colorCompare(data[i], Color{255, 255, 0, 255})) {
            current = Tile::ROAD;
        } else if (CT::colorCompare(data[i], Color{255, 255, 255, 255})) {
            current = Tile::TOUREL;
            this->placeholders.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost, current});
        } else if (CT::colorCompare(data[i], Color{0, 0, 255, 255})) {
            current = Tile::START;
            this->spawns.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost, current});
        } else if (CT::colorCompare(data[i], Color{255, 0, 0, 255})) {
            current = Tile::FINISH;
            this->goals.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost, current});
        } else {
            current = Tile::GRASS;
        }
        cost = tile_costs.find(current)->second; // getting enum value
        this->data[i] = MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost, current};
    }
    free(data);
}

Map::~Map() {
    free(this->data);
}

Map Map::loadFromFile(Scene& parent, const char* filename) {
    File map_file(filename);
    std::string map_text = map_file.getText();
    int width, height;
    int previous_pos, channels = 3, nowChannel = 0, actual_size = 0;
    char *colorByte;
    // Image im;
    Color *map;
    char current;

    for (int i = 0; map_text[i] != '\0'; i++) {
        current = map_text[i];
        switch(current) {
            case '#':
                while(map_text[++i] != '\n');
                previous_pos = ++i;
                break;
            case ' ':
                width = stod(map_text.substr(previous_pos, i - previous_pos));
                previous_pos = ++i;
                while (map_text[++i] != '\n');
                height = stod(map_text.substr(previous_pos, i - previous_pos));
                while (map_text[++i] != '\n');
                previous_pos = ++i;
                map = (Color*)malloc(width*height*sizeof(Color));
                break;
            case 'P':
                previous_pos = ++i;
                channels = stod(map_text.substr(previous_pos, ++i - previous_pos));
                
                colorByte = (char*)malloc(channels);
                while (map_text[++i] != '\n');
                previous_pos = ++i;
                break;
            case '\n':
                // cout << (int)stod(map_text.substr(previous_pos, i-previous_pos)) << endl;
                if (actual_size >= width*height) {
                    previous_pos = i+1;
                    break;
                }
                colorByte[nowChannel] = (int)stod(map_text.substr(previous_pos, i-previous_pos));
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
    free(colorByte);
    return Map(parent, width, height, map);
}

Vector2 Map::getSize() {
    return Vector2{1.f*this->width, 1.f*this->height};
}

MapUnit* Map::operator[](int index) {
    if (index >= this->height) return nullptr;
    return &this->data[index*this->width];
}

void Map::draw(float scale, Vector2 camera) {
    int wid = this->getSize().x, hei = this->getSize().y;
    for (int i = 0; i < hei; i++) {
        for (int j = 0; j < wid; j++) {
            DrawRectangle(
                (j - camera.x)*scale + Window::getInstance()->getSize().x * 0.5f, 
                (i - camera.y)*scale + Window::getInstance()->getSize().y * 0.5f, 
                scale, scale, (*this)[i][j].color);
        }
    }
}

void Map::update(float deltaTime) {
    if (GetTime() - lastSpawned > 1.f) {
            MapUnit startUnit = getAny(Tile::START);
            std::shared_ptr<Creep> temp(
                        new Creep( parent,
                            {startUnit.position.x, startUnit.position.y + 0.5f}, 
                            (new Path(startUnit.position, startUnit.cost))->findPathAndBuild(this, getAny(Tile::FINISH)),
                            5.f,
                            8,
                            (std::string("level/demo/") + std::string("Zombie.png")).c_str(),
                            3
                        )
                );
            temp->setColor(RED);
            parent.add(temp);
            Path::cleanUp();
            lastSpawned = GetTime();
        }
}

/**
 * @return MapUnit value if at least one spawn point exists,
 * MapUnit with cost = 0 otherwise
*/
MapUnit Map::getAny(Tile_t type) {
    std::vector<MapUnit> temp;
    switch (type) {
        case Tile::FINISH:
            temp = goals;
            break;
        default:
            temp = spawns;
            break;
    }
    if (temp.size() <= 0) return MapUnit{{0, 0, 0}, {0.f, 0.f}, 0};
    timeval time;
    gettimeofday(&time, nullptr);
    srand(time.tv_usec);
    return temp[rand() % temp.size()];
}

void Map::clear() {
        std::map<Tile_t, uint32_t> tile_costs = {
        {Tile::ROAD, uint32_t(1)},
        {Tile::START, uint32_t(1)},
        {Tile::FINISH, uint32_t(1)},
        {Tile::TOUREL, 2147000000},
        {Tile::GRASS, 2147000000}
    };
    for (int i = 0; i < width*height; i++) {
        uint32_t cost = 1;
        Tile_t current;
        if (CT::colorCompare(data[i].color, Color{255, 255, 0, 255})) {
            current = Tile::ROAD;
        } else if (CT::colorCompare(data[i].color, Color{255, 255, 255, 255})) {
            current = Tile::TOUREL;
        } else if (CT::colorCompare(data[i].color, Color{0, 0, 255, 255})) {
            current = Tile::START;
        } else if (CT::colorCompare(data[i].color, Color{255, 0, 0, 255})) {
            current = Tile::FINISH;
        } else {
            current = Tile::GRASS;
        }
        data[i].cost = tile_costs.find(current)->second; // getting enum value
    }
}
