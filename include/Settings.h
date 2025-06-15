#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"

// Technical Stuff
extern Vector2 window;
extern const Vector2 V_SCREEN;
extern const int BG_LOOPING_POINT, GROUND_LOOPING_POINT;
extern const int TARGET_FPS;

// Bird
extern const int GRAVITY;
extern const int JUMP_BURST;
extern const int HITBOX_LEEWAY;

// Pipes
extern const int PIPE_GAP;
extern const int PIPE_TOP_MARGIN;
extern const int PIPE_BOTTOM_MARGIN;
extern const int PIPE_SHIFT;
extern const int SPAWN_TIME;

// Scenery
extern const float BG_SCROLL_SPEED;
extern const float GROUND_SCROLL_SPEED;
extern const float PIPE_SCROLL_SPEED;

#endif