// TODO add rotation to Bird

#include "Bird.h"
#include "Assets_paths.h"
#include "Settings.h"
#include "raylib.h"

// Prototypes
// ----------
static bool canJump(void);
// ----------

Bird *NewBird(Vector2 screen) {
  static Bird newBird = {0};
  newBird.birdSprite = LoadTexture(BIRD_IMG);

  newBird.width = newBird.birdSprite.width;
  newBird.height = newBird.birdSprite.height;

  newBird.pos.x = (screen.x - newBird.width) / 2;
  newBird.pos.y = (screen.y - newBird.height) / 2;

  newBird.hitBox.width = newBird.width - 2 * HITBOX_LEEWAY;
  newBird.hitBox.height = newBird.height - 2 * HITBOX_LEEWAY;

  return &newBird;
}

void BirdUpdate(Bird *bird, float dt) {
  bird->dy += GRAVITY * dt;

  if (canJump()) {
    bird->dy -= JUMP_BURST;
  }

  bird->pos.y += bird->dy;

  bird->hitBox.x = bird->pos.x + HITBOX_LEEWAY;
  bird->hitBox.y = bird->pos.y + HITBOX_LEEWAY;
}

static bool canJump(void) { return IsKeyPressed(KEY_SPACE); }

void BirdDraw(Bird *bird) {
  DrawTexture(bird->birdSprite, bird->pos.x, bird->pos.y, WHITE);
  // DrawTextureEx(bird->birdSprite, bird->pos, bird->rotation, 1.0f, WHITE);
}
