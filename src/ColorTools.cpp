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