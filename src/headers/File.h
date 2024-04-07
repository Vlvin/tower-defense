#pragma once

#include <string>
class File {
protected:
    char* text;
public:
    std::string getText();
    File(const char* filename);
    ~File();
};