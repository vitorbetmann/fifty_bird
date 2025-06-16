#ifndef STATE_TITLE_SCREEN_H
#define STATE_TITLE_SCREEN_H

// Includes
// --------
#include "Bird.h"
// --------

// Prototypes
// ----------
void StateTitleEnter(void);
void StateTitleUpdate(float dt);
void StateTitleDraw(void);
Bird *StateTitleExit(void);
// ----------

#endif