#include "ColorTools.h"




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
        (int(precition*a.x) == int(precition*b.x)) &&
        (int(precition*a.y) == int(precition*b.y))
    );
}