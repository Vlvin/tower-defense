#include "Map.h"
#include "File.h"
#include "string"
#include <malloc.h>

// Map type
Map::Map(int width, int height, Color* data) {
    this->width = width;
    this->height = height;
    this->data = data;
}

Map::~Map() {
    free(this->data);
}

Map Map::load(const char* filename) {
    File map_file("map.ppm");
    std::string map_text = map_file.getText();
    int width, height;
    int previous_pos, channels = 3, nowChannel = 0, actual_size = 0;
    char *colorByte;
    Image im;
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

Color* Map::operator[](int index) {
    if (index >= this->height) return nullptr;
    return &this->data[index*this->width];
}
