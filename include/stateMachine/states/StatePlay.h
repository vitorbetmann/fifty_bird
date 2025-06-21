#ifndef PLAY_STATE_H
#define PLAY_STATE_H

// Includes
// #include "stateMachine/StateMachine.h"
#include "../../smile_engine/include/smile.h"
#include <raylib.h>

// Data Types
// ----------
typedef struct {
  int score;
} ScoreArgs;

// --------
// Prototypes
// ----------
void StatePlayEnter(void *args);
void StatePlayUpdate(float dt);
void StatePlayDraw(void);
void StatePlayExit(void);
// ----------

// Variables
// ---------
extern State statePlay;
extern Texture pauseImg;

#endif