#include "Picture.h"
#include <iostream>


Picture::Picture(const char* path) {
    this->image = LoadImage(path);
    this->texture = LoadTextureFromImage(image);
}

Picture::~Picture() {
    UnloadImage(image);
    UnloadTexture(texture);
}

Image Picture::getImage() {
    return image;
}

Texture2D Picture::getTexture() {
    return texture;
}