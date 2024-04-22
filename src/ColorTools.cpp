#include "ColorTools.h"
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
    int x = round(position.x*precition);
    int y = round(position.y*precition);
    return (
        (round((box.x - radius)*precition) <= x) && (x <= round((box.x + box.width + radius)*precition)) &&
        (round((box.y - radius)*precition) <= y) && (y <= round((box.y + box.height + radius)*precition))
    );
}