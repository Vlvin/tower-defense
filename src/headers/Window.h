#pragma once
#include <raylib.h>
#include <string>
// "more back - less front" this class provides functionality just to create window

class Window { 
protected:
    static Window* instance;
    int width, height;
    std::string title;
    Window(int width, int height, const char *title);
public:
    static Window* getInstance(int width = 100, int height = 100, const char* title = "Unnamed");
    ~Window();
    Vector2 getSize();
    std::string getName();
};