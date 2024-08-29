#pragma once



// 0 layer
inline const int SCENE_DRAW_LAYER = 0;

// 1 layer
inline const int MAP_DRAW_LAYER = SCENE_DRAW_LAYER + 1;

// 2 layer
inline const int CREEP_DRAW_LAYER = MAP_DRAW_LAYER + 1;
inline const int TOUREL_DRAW_LAYER = CREEP_DRAW_LAYER;
inline const int BULLET_DRAW_LAYER = CREEP_DRAW_LAYER+1;

// 3 layer
inline const int BUTTON_DRAW_LAYER = BULLET_DRAW_LAYER + 1;
