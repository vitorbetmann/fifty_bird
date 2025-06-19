#include "stateMachine/StateMachine.h"
#include <stdlib.h>

// Data types
// ----------

// Variables
// ---------
State *currState;

void SMChangeState(State *state, void *args) {
  if (currState && currState->Exit) {
    currState->Exit();
  }

  currState = state;

  if (currState && currState->Enter) {
    currState->Enter(args);
  }
}