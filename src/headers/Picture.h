#pragma once
#include <raylib.h>

class Picture {
    Image image;
    Texture2D texture;
public:
    Picture(const char* path);
    ~Picture();
    Image getImage();
    Texture2D getTexture();
};
