#ifndef PIPE_H
#define PIPE_H
#include "raylib.h"

// Data types
// ----------
typedef enum { TOP, BOTTOM } Orientation;

typedef struct {
  Texture2D sprite;
  int width, height;
  Orientation orientation;
  Vector2 pos;
} Pipe;

// Prototypes
// ----------
void PipeLoadSprite(void);
Pipe *NewPipe(Vector2 screen, Orientation orientation);
void PipeUpdate(Pipe *pipe, float dt);
void PipeDraw(Pipe *pipe);
void PipeUnloadSprite();
// ----------

#endif