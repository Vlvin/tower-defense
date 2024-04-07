#pragma once


class Path {
protected:
    Path* prev;
    int cost;
public:
    Path(int cost, Path* prev = nullptr);
    int getSize();
    bool isAlreadyPassed(unsigned int max_depth);
    Path* allocator();
};
