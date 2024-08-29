#pragma once
#include <raylib.h>


namespace CT {
  bool colorCompare(Color a, Color b, bool useAlpha = false);
  bool vec2Compare(Vector2 a, Vector2 b, float precition = 1.f);
  float vec2Distance(Vector2 a, Vector2 b);
  float vec2Length(Vector2 a);
  bool isCircleInBox2(Vector2 position, float radius, Rectangle box, float precition = 1.f);
  bool boxCollision(Rectangle a, Rectangle b, float precition = 1.f);
}