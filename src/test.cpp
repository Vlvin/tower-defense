#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdarg>
#include <sys/time.h>
#include <fstream>
#include <algorithm>
#include <csignal>

#include "Map.h"
#include "Window.h"
#include "PathFinder.h"
#include "ColorTools.h"
#include "Creep.h"

using namespace std;


fstream fout;

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

    signal(SIGEV_SIGNAL, Path::cleanUp);


    char help_msg[300];
    strcat(help_msg, "tests");
    strcat(help_msg, 
        "\n"
        "Arguments:\n"
        "-s <x> <y> : add start point\n"
        "-e <x> <y> : add end point\n"
        "every point requires 2 int values as arguments\n"
    );
    fout = fstream("./build/log.txt", ios::out);
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
        log("Test not passed: %d of %d passed", valid_counter, valid_counter+invalid_counter);
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
        log("Test not passed: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    } else {
        log("Test passed OK: %d of %d passed", valid_counter, valid_counter+invalid_counter);
    }



    log("\nBegin Path speed test");
    MapUnit start = map.getAny(Tile::START);
    if (!start.cost) {
        log("Are you serious? No spawnpoints on Test? Now go and add them");
        MapUnit start = map[0][0];
    }
    timeval beg, end;
    // getting resource for length count
    Path *first = new Path(start.position, start.cost);
    std::vector<std::vector<Path*>> pathPaths = {first->getNeighbours(&map)};
    std::vector<Path*> temp;

    log("\nPath speed test: create Path test");
    gettimeofday(&beg, NULL);

    pathPaths.push_back({new Path(start.position, start.cost)});
    for (int i = 0; i < 5; i++) {
        pathPaths.push_back({});
        for (int j = 0; j < pathPaths[i].size(); j++) {
            temp = pathPaths[i][j]->getNeighbours(&map);
            for (int k = 0; k < temp.size(); k++) 
                pathPaths[i+1].push_back(temp[k]);
        }
    }
    pathPaths.pop_back();

    gettimeofday(&end, NULL);
    int last_level = pathPaths.size() - 1;
    log("5 level of path depth created for %f seconds with %d paths", (end.tv_sec-beg.tv_sec)+(end.tv_usec-beg.tv_usec)*0.000001f, pathPaths[last_level].size());
    log("Last level pointer %p\n", pathPaths[last_level][pathPaths[last_level].size() - 1]->allocator());

    log("Path speed test: Length count test");
    gettimeofday(&beg, NULL);

    log("Path length is: %d", pathPaths[pathPaths.size() - 1][pathPaths[pathPaths.size() - 1].size() - 1]->getFullCost());

    gettimeofday(&end, NULL);
    log("Path length calculated for %f seconds\n", (end.tv_sec-beg.tv_sec)+(end.tv_usec-beg.tv_usec)*0.000001f);

    log("Path speed test: Path finding test");
    MapUnit finnish = map.getAny(Tile::FINISH);
    Path::cleanUp();
    first = new Path(start.position, start.cost);

    log("searching for %f:%f", finnish.position.x, finnish.position.y);
    gettimeofday(&beg, NULL);

    Path *last = first->findPath(&map, finnish); 

    gettimeofday(&end, NULL);
    log("Found in %f seconds", (end.tv_sec-beg.tv_sec)+(end.tv_usec-beg.tv_usec)*0.000001f);
    log("Last Path is: %p on %fx%f coordinates\n", last->allocator(), last->getPosition().x, last->getPosition().y); 
 
    log("Path speed test: Path Setting up test");
    log("Setting route back to %p", first);
    gettimeofday(&beg, NULL);

    Path *first_copy = last->setRouteFromStart(); 

    gettimeofday(&end, NULL);

    Path *last_copy = first_copy; 
    
    while(last_copy->getNext() != nullptr) {
        last_copy = last_copy->getNext();
    }


    if (first_copy != first) {
        log("Test not passed: first cell %p is not same %p", first_copy, first);
    } else if (last_copy != last) {
        log("Test not passed: last cell %p is not same %p", last_copy, last);
    } else  {
        log("Test passed OK: route set up in %f sec", (end.tv_sec-beg.tv_sec)+(end.tv_usec-beg.tv_usec)*0.000001f);
    }

    log("Begin Creep test");
    log("Creep test: movements");

    // Window win(20*width, 20*height, "PathFinderTest");

    // Creep creep(start.position, first);
    
    // gettimeofday(&beg, NULL);

    // SetTargetFPS(60);
    // while (!CT::vec2Compare(creep.getPosition(), last->getPosition(), 1.1f))
    // {   
    //     creep.update(0.10f);
    //     BeginDrawing();
    //         ClearBackground(BLACK);
    //         map.draw(20.f);
    //         creep.draw(20.f);
    //     EndDrawing(); 
    //     log("%f:%f  ->  %f:%f  : %d\n", creep.getPosition().x, creep.getPosition().y, creep.getTarget().x, creep.getTarget().y, creep.getIndex());
    // }


    log("Creep test: movements - skipped");
    

    // gettimeofday(&end, NULL);



    Path::cleanUp();
    fout.close();
    return 0;
}