#include "ColorTools.hpp"
#include <iostream>
#include <cmath>



bool CT::colorCompare(Color a, Color b, bool useAlpha) {
    return (
        (a.r == b.r) &&
        (a.g == b.g) &&
        (a.b == b.b) &&
        (useAlpha ? (a.a == b.a) : true)
    );
}

bool CT::vec2Compare(Vector2 a, Vector2 b, float precition) {
    return (
        (round(precition*a.x) == round(precition*b.x)) &&
        (round(precition*a.y) == round(precition*b.y))
    );
}

float CT::vec2Length(Vector2 a) {
    return sqrt((a.x*a.x) + (a.y*a.y));
}

float CT::vec2Distance(Vector2 a, Vector2 b) {
    return vec2Length({a.x-b.x, a.y-b.y});
}

bool CT::isCircleInBox2(Vector2 position, float radius, Rectangle box, float precition) {
    // std::cout << round(position.x*precition) << ":";
    int x = round(position.x*precition);
    int y = round(position.y*precition);

    // std::cout << x << '\n';
    return (
        (round((box.x - radius)*precition) <= x) && (x <= round((box.x + box.width + radius)*precition)) &&
        (round((box.y - radius)*precition) <= y) && (y <= round((box.y + box.height + radius)*precition))
    );
}

bool CT::boxCollision(Rectangle a, Rectangle b, float precition) {
    int ax = round(a.x*precition), 
        ay = round(a.y*precition), 
        aw = round(a.width*precition), 
        ah = round(a.height*precition);
    int bx = round(b.x*precition), 
        by = round(b.y*precition), 
        bw = round(b.width*precition), 
        bh = round(b.height*precition);
    return (

        (ax < bx + bw) &&
        (ax + aw > bx) &&
        (ay < by + bh) &&
        (ay + ah > by)
    );
}