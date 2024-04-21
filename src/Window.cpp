
#include "Window.h"
#include <iostream>

Window* Window::instance = nullptr;

Window::Window(int width, int height, const char* title) {
    InitWindow(width, height, title);
    this->width = width;
    this->height = height;
    this->title = std::string(title);
}

Window* Window::getInstance(int width, int height, const char* title) {
    if (!instance) {
        instance = new Window(width, height, title);
    }
    return instance;
}

Window::~Window() {
    CloseWindow();
    delete instance;
}

Vector2 Window::getSize() {
    return {width, height};
}

std::string Window::getName() {
    return title;
}