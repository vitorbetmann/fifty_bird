#ifndef PIPE_H
#define PIPE_H
#include "raylib.h"

// Data types
// ----------
typedef struct {
  Texture2D sprite;
  int width, height;
  Vector2 pos;
} Pipe;

// Prototypes
// ----------
void PipeInit(void);
Pipe *NewPipe(Vector2 screen);
void PipeUpdate(Pipe *pipe, float dt);
void PipeDraw(Pipe *pipe);

// Variables
// ---------
extern Texture2D PIPE_SPRITE;
#endif