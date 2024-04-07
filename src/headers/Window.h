#pragma once
#include <raylib.h>

// "more back - less front" this class provides functionality just to create window
class Window { 
protected:
    
public:
    Window(int width, int height, const char *title);
    ~Window();
};