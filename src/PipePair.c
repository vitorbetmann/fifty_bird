#include "PipePair.h"
#include "Pipe.h"
#include "Settings.h"
#include "raylib.h"
#include <stdlib.h>

const int PIPE_HEIGHT = 288;

PipePair *NewPipePair(Vector2 gapPos) {
  PipePair *newPipePair = malloc(sizeof(PipePair));

  newPipePair->top = NewPipe((Vector2){gapPos.x, gapPos.y - PIPE_HEIGHT}, TOP);
  newPipePair->bottom = NewPipe(
      (Vector2){gapPos.x, newPipePair->top->pos.y + PIPE_HEIGHT + PIPE_GAP},
      BOTTOM);

  newPipePair->width = newPipePair->bottom->width;
  newPipePair->pos = &newPipePair->bottom->pos;

  newPipePair->score = PIPE_SCORE;

  return newPipePair;
}

void PipePairUpdate(PipePair *pipePair, float dt) {
  PipeUpdate(pipePair->top, dt);
  PipeUpdate(pipePair->bottom, dt);
}

void PipePairDraw(PipePair *pipePair) {
  PipeDraw(pipePair->top);
  PipeDraw(pipePair->bottom);
}

void PipePairUnload(PipePair *pipePair) {
  free(pipePair->bottom);
  free(pipePair->top);
}