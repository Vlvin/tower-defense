#include "File.h"
#include <raylib.h>


File::File(const char* filename) {
    this->text = LoadFileText(filename);
}

File::~File() {
    UnloadFileText(this->text);
}

std::string File::getText() {
    return std::string(this->text);
}