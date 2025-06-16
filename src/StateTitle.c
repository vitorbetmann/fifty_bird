#include "states/StateTitle.h"

// Inlcudes
// --------
#include "Settings.h"
// --------

// Variables
// ---------
static Bird *bird;
// ---------

void StateTitleEnter(void) { bird = NewBird(V_SCREEN); }

void StateTitleUpdate(float dt) {
  // Nothing to do
}

void StateTitleDraw(void) { BirdDraw(bird); }

Bird *StateTitleExit(void) { return bird; }
