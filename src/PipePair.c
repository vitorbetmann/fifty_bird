#include "PipePair.h"
#include "Pipe.h"
#include "raylib.h"
#include <stdlib.h>

float lastY;
static const int PIPE_HEIGHT = 288;

void PipePairInit() { lastY = -PIPE_HEIGHT + GetRandomValue(0, 80) + 20; }

PipePair *NewPipePair(Vector2 screen) {
  PipePair *newPipePair = malloc(sizeof(PipePair));
  newPipePair->top = NewPipe(screen, TOP);
  newPipePair->bottom = NewPipe(screen, BOTTOM);
  newPipePair->width = &newPipePair->bottom->width;
  newPipePair->pos = &newPipePair->bottom->pos;

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