#include "Map.h"
#include "File.h"
#include "ColorTools.h"
#include <map>
#include <cmath>
#include <string>
#include <sys/time.h>
#include <malloc.h>

// Map type
Map::Map(int width, int height, Color* data) {
    this->width = width;
    this->height = height;
    this->data = (MapUnit*)malloc(width*height*sizeof(MapUnit));
    std::map<Tile_t, uint32_t> tile_costs = {
        {Tile::ROAD, 1},
        {Tile::START, 1},
        {Tile::FINISH, 1},
        {Tile::TOUREL, 100},
        {Tile::GRASS, 100}
    };
    for (int i = 0; i < width*height; i++) {
        uint32_t cost = 1;
        Tile_t current;
        if (CT::colorCompare(data[i], Color{255, 255, 0, 255})) {
            current = Tile::ROAD;
        } else if (CT::colorCompare(data[i], Color{255, 255, 255, 255})) {
            current = Tile::TOUREL;
            this->placeholders.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost});
        } else if (CT::colorCompare(data[i], Color{0, 0, 255, 255})) {
            current = Tile::START;
            this->spawns.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost});
        } else if (CT::colorCompare(data[i], Color{255, 0, 0, 255})) {
            current = Tile::FINISH;
            this->goals.push_back(MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost});
        } else {
            current = Tile::GRASS;
        }
        cost = tile_costs.find(current)->second; // getting enum value
        this->data[i] = MapUnit{data[i], Vector2{1.f*(i%width), (float)floor(((float)i)/width)}, cost};
    }
    free(data);
}

Map::~Map() {
    free(this->data);
}

Map Map::loadFromFile(const char* filename) {
    File map_file("map.ppm");
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
    return Map(width, height, map);
}

Vector2 Map::getSize() {
    return Vector2{1.f*this->width, 1.f*this->height};
}

MapUnit* Map::operator[](int index) {
    if (index >= this->height) return nullptr;
    return &this->data[index*this->width];
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
