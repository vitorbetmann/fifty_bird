#include "Pipe.h"
#include "Assets_paths.h"
#include "Settings.h"
#include "raylib.h"
#include "stdlib.h"

Texture2D PIPE_SPRITE;

void PipeInit() { PIPE_SPRITE = LoadTexture(PIPE_IMG); }

Pipe *NewPipe(Vector2 screen) {
  Pipe *newPipe = malloc(sizeof(Pipe));
  newPipe->sprite = PIPE_SPRITE;
  newPipe->pos.x = screen.x;
  newPipe->pos.y = GetRandomValue(screen.y / 4, screen.y - 10);
  newPipe->width = newPipe->sprite.width;
  newPipe->height = newPipe->sprite.height;

  return newPipe;
}

void PipeUpdate(Pipe *pipe, float dt) { pipe->pos.x -= PIPE_SCROLL_SPEED * dt; }

void PipeDraw(Pipe *pipe) {
  DrawTexture(pipe->sprite, pipe->pos.x, pipe->pos.y, WHITE);
}