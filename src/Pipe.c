#include "Pipe.h"
#include "Assets_paths.h"
#include "Settings.h"
#include "raylib.h"
#include "stdlib.h"

static Texture2D PIPE_SPRITE;
static bool spriteLoaded = false;

void PipeLoadSprite() {
  if (!spriteLoaded) {
    PIPE_SPRITE = LoadTexture(PIPE_IMG);
    spriteLoaded = true;
  }
}

Pipe *NewPipe(Vector2 pos, Orientation orientation) {
  Pipe *newPipe = malloc(sizeof(Pipe));
  if (newPipe == NULL) {
    return NULL;
  }

  if (!spriteLoaded) {
    PipeLoadSprite();
  }

  newPipe->sprite = PIPE_SPRITE;
  newPipe->orientation = orientation;
  newPipe->pos.x = pos.x;
  newPipe->pos.y = pos.y;
  newPipe->width = newPipe->sprite.width;
  newPipe->height = newPipe->sprite.height;

  return newPipe;
}

void PipeUpdate(Pipe *pipe, float dt) { pipe->pos.x -= PIPE_SCROLL_SPEED * dt; }

void PipeDraw(Pipe *pipe) {
  if (pipe->orientation == TOP) {
    Rectangle source = {0, 0, pipe->width, -pipe->height};
    Rectangle dest = {pipe->pos.x, pipe->pos.y, pipe->width, pipe->height};

    DrawTexturePro(pipe->sprite, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
  } else {
    DrawTexture(pipe->sprite, pipe->pos.x, pipe->pos.y, WHITE);
  }
}

void PipeUnloadSprite() { UnloadTexture(PIPE_SPRITE); }