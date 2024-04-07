#include "Window.h"

Window::Window(int width, int height, const char* title) {
    InitWindow(width, height, title);
}

Window::~Window() {
    CloseWindow();
}