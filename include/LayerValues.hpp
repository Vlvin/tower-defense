#pragma once



// 0 layer
inline const int SCENE_DRAW_LAYER = 0;

// 1 layer
inline const int MAP_DRAW_LAYER = SCENE_DRAW_LAYER + 1;

// 2
inline const int PLACEHOLDER_DRAW_LAYER = MAP_DRAW_LAYER+1;
inline const int SPAWNER_DRAW_LAYER = PLACEHOLDER_DRAW_LAYER;

// 3
inline const int CREEP_DRAW_LAYER = PLACEHOLDER_DRAW_LAYER + 1;


inline const int BULLET_DRAW_LAYER = CREEP_DRAW_LAYER+1;

// 4 
inline const int TOUREL_DRAW_LAYER = BULLET_DRAW_LAYER+1;

inline const int BUTTON_DRAW_LAYER = TOUREL_DRAW_LAYER + 1;

// 5 
inline const int HUD_DRAW_LAYER = BUTTON_DRAW_LAYER + 1;
