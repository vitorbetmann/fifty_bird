#include "Bird.h"
#include "Assets_paths.h"
#include "Settings.h"
#include "raylib.h"

Bird *NewBird(Vector2 screen) {
  static Bird newBird = {0};
  newBird.birdSprite = LoadTexture(BIRD_IMG);
  newBird.birdWidth = newBird.birdSprite.width;
  newBird.birdHeight = newBird.birdSprite.height;
  newBird.pos.x = (screen.x - newBird.birdWidth) / 2;
  newBird.pos.y = (screen.y - newBird.birdHeight) / 2;

  return &newBird;
}

void BirdUpdate(Bird *bird, float dt) {
  bird->dy += GRAVITY * dt;

  if (canJump()) {
    bird->dy -= JUMP_BURST;
  }

  bird->pos.y += bird->dy;
}

bool canJump(void) { return IsKeyPressed(KEY_SPACE); }

void BirdDraw(Bird *bird) {
  DrawTextureEx(bird->birdSprite, bird->pos, bird->rotation, 1.0f, WHITE);
}
