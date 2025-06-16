#ifndef STATE_COUNTDOWN_H
#define STATE_COUNTDOWN_H

// Includes
// --------
#include "Bird.h"

// Prototypes
// ----------
void StateCountdownEnter(Bird *player);
void StateCountdownUpdate(float dt);
bool IsTimerOver(void);
void StateCountdownDraw(void);
void StateCountdownExit(void);

#endif