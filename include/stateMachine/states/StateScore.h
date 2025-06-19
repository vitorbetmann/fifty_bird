#ifndef STATE_SCORE_H
#define STATE_SCORE_H

// Includes
// --------
#include "stateMachine/StateMachine.h"
#include <raylib.h>

// Prototypes
// ----------
void StateScoreEnter(void *args);
void StateScoreUpdate(float dt);
void StateScoreDraw(void);

// Variables
// ---------
extern State stateScore;
extern Texture2D medalGoldImg, medalSilverImg, medalBronzeImg;

#endif