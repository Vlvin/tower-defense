#pragma once
#include <raylib.h>
#include <string>

#include "File.h"
#include "Map.h"

using namespace std;



namespace ML {
    Map load(const char* filename);
}