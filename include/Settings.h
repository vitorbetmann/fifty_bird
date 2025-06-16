#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"

// Title
extern const char *const GAME_TITLE;

// Window
extern Vector2 window;
extern const Vector2 V_SCREEN;
extern const int TARGET_FPS;

// Fonts
extern Font smallFont, mediumFont, flappyFont, hugeFont;
extern const int SMALL_FONT_SIZE;
extern const int MEDIUM_FONT_SIZE;
extern const int HUGE_FONT_SIZE;
extern const int FLAPPY_FONT_SIZE;

// Music
extern Music music;

// Sounds
extern Sound explosionSound, hurtSound, jumpSound, scoreSound;

// Controls
extern bool (*HasValidInput)(int value);
extern int input1, input2;

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
extern const int PIPE_SCORE;

// Scenery
extern const int BG_LOOPING_POINT, GROUND_LOOPING_POINT;
extern const float BG_SCROLL_SPEED, GROUND_SCROLL_SPEED, PIPE_SCROLL_SPEED;

#endif