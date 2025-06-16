#ifndef PLAY_STATE_H
#define PLAY_STATE_H

// Includes
// --------
#include "Bird.h"
// --------

// --------
// Prototypes
// ----------
void StatePlayEnter(Bird *player);
void StatePlayUpdate(float dt);
void StatePlayDraw(void);
void StatePlayExit(void);
// ----------

#endif