#ifndef STATE_TITLE_SCREEN_H
#define STATE_TITLE_SCREEN_H

// Includes
// --------
#include "Bird.h"
// --------

// Prototypes
// ----------
void StateTitleEnter(Bird *player);
void StateTitleUpdate(float dt);
void StateTitleDraw(void);
void StateTitleExit(void);
// ----------

#endif