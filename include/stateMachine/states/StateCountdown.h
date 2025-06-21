#ifndef STATE_COUNTDOWN_H
#define STATE_COUNTDOWN_H

// Includes
// --------
#include "../../smile_engine/include/smile.h"
// #include "stateMachine/StateMachine.h"

// Prototypes
// ----------
void StateCountdownEnter(void *args);
void StateCountdownUpdate(float dt);
void StateCountdownDraw(void);

// Variables
// ---------
extern State stateCountdown;

#endif