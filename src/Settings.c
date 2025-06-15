#include "Settings.h"

// Technical Stuff
Vector2 window = {1280, 720};
const Vector2 V_SCREEN = {512, 288};
const int BG_LOOPING_POINT = 413, GROUND_LOOPING_POINT = V_SCREEN.x;
const int TARGET_FPS = 30;

// Bird
const int GRAVITY = 20;
const int JUMP_BURST = 8;
const int HITBOX_LEEWAY = 2;

// Pipes
const int PIPE_GAP = 90;
const int PIPE_TOP_MARGIN = 30;
const int PIPE_BOTTOM_MARGIN = 45;
const int PIPE_SHIFT = 20;
const int SPAWN_TIME = 2;

// Scenery
const float BG_SCROLL_SPEED = 30.0f;
const float GROUND_SCROLL_SPEED = 60.0f;
const float PIPE_SCROLL_SPEED = GROUND_SCROLL_SPEED;