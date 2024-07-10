#pragma once
#include <raylib.h>


namespace CT {
    inline bool colorCompare(Color a, Color b, bool useAlpha = false);
    inline bool vec2Compare(Vector2 a, Vector2 b, float precition = 1.f);
    inline float vec2Distance(Vector2 a, Vector2 b);
    inline float vec2Length(Vector2 a);
    inline bool isCircleInBox2(Vector2 position, float radius, Rectangle box, float precition = 1.f);
    inline bool boxCollision(Rectangle a, Rectangle b, float precition = 1.f);
}