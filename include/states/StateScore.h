#ifndef STATE_SCORE_H
#define STATE_SCORE_H

// Includes
// --------
#include "Bird.h"

// Prototypes
// ----------
void StateScoreEnter(Bird *player);
void StateScoreUpdate(float dt);
void StateScoreDraw(void);
void StateScoreExit(void);

#endif