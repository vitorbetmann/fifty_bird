#ifndef STATE_COUNTDOWN_H
#define STATE_COUNTDOWN_H

// Prototypes
// ----------
void StateCountdownEnter(void);
void StateCountdownUpdate(float dt);
bool IsTimerOver(void);
void StateCountdownDraw(void);
void StateCountdownExit(void);

#endif