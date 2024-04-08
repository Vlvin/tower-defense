#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdarg>
#include <fstream>
#include <algorithm>

#include "Map.h"
#include "PathFinder.h"
#include "ColorTools.h"

using namespace std;


fstream fout("./build/log.txt", ios::out);

int vec2count(vector<Vector2> where, Vector2 target) {
    int counter = 0;
    for (int i = 0; i < where.size(); i++) {
        if (CT::vec2Compare(where.at(i), target)) counter++;
    }
    return counter;
}

void log(const char* format, ...) {
    char *message;
    va_list args;
    va_start(args, format);
    if(0 > vasprintf(&message, format, args)) message = NULL;
    va_end(args);
    if(message) {
        cout << message << endl;
        fout << message << endl;
    }
}

int main(int argc, char *argv[]) {
    char help_msg[300];
    strcat(help_msg, "tests");
    strcat(help_msg, 
        "\n"
        "Arguments:\n"
        "-s <x> <y> : add start point\n"
        "-e <x> <y> : add end point\n"
        "every point requires 2 int values as arguments\n"
    );
    std::vector<Vector2> starts, goals;
    // // image parsing
    Vector2 point;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "--help")) {
            log(help_msg);
            return 0;
        }
        if (!strcmp(argv[i], "-s")) {
            if ((argc - 2) <= i) { 
                log("Not enought argues on: %s\n%s --help for help", argv[i], argv[0]);
                return -1;
            }
            const char *x = argv[++i], *y = argv[++i];
            starts.push_back({(float)stod(x), (float)stod(y)});
        }
        if (!strcmp(argv[i], "-e")) {
            if ((argc - 2) < i) { 
                log("Not enought argues on: %s\n%s --help for help", argv[i], argv[0]);
                return -1;
            }
            const char *x = argv[++i], *y = argv[++i];
            goals.push_back({(float)stod(x), (float)stod(y)});
        }
    }
    Map map = Map::loadFromFile("map.ppm");
    int width = map.getSize().x;
    int height = map.getSize().y;
    
    // valid starts test
    log("\nBegin start point test");
    int invalid_counter = 0, valid_counter = 0;
    for (int i = 0; i < 1000; i++) {
        MapUnit start = map.getAny(Tile::START);
        if (!start.cost) {
            fout << ("Are you serious? No spawnpoints on Test? Now go and add them");
        }
        if (vec2count(starts, start.position) <= 0) {
            invalid_counter++;
            fout << "invalid start point on: " << int(start.position.x) << ":" << int(start.position.y) << "\n";
        } else {
            valid_counter++;
        }
    }
    if (invalid_counter) {
        log("Test passed OK: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    } else {
        log("Test passed OK: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    }
    log("\nBegin end point test");
    invalid_counter = 0, valid_counter = 0;
    for (int i = 0; i < 1000; i++) {
        MapUnit goal = map.getAny(Tile::FINISH);
        if (!goal.cost) {
            log("Are you serious? No spawnpoints on Test? Now go and add them");
        }
        if (vec2count(goals, goal.position) <= 0) {
            invalid_counter++;
            log("invalid end point on: %d:%d", int(goal.position.x), int(goal.position.y));
        } else {
            valid_counter++;
        }
    }
    if (invalid_counter) {
        log("Test passed OK: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    } else {
        log("Test passed OK: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    }
    Path::cleanUp();
    return 0;
}