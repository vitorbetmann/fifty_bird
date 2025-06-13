#include "Settings.h"

// Technical Stuff
Vector2 window = {1280, 720};
const Vector2 V_SCREEN = {512, 288};
const int BG_LOOPING_POINT = 413, GROUND_LOOPING_POINT = V_SCREEN.x;
const int TARGET_FPS = 30;

// Bird
const int GRAVITY = 20;
const int JUMP_BURST = 5;

// Scenery
const int BG_SCROLL_SPEED = 30;
const int GROUND_SCROLL_SPEED = 60;
const int PIPE_SCROLL_SPEED = GROUND_SCROLL_SPEED;