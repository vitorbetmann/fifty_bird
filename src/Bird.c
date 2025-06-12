#include "Bird.h"
#include "Assets_paths.h"
#include "Settings.h"

Bird *BirdInit(Vector2 screen) {
  static Bird newBird;
  newBird.birdImg = LoadTexture(BIRD_IMG);
  newBird.birdWidth = newBird.birdImg.width;
  newBird.birdHeight = newBird.birdImg.height;
  newBird.x = (screen.x - newBird.birdWidth) / 2;
  newBird.y = (screen.y - newBird.birdHeight) / 2;
  newBird.dy = 0;

  return &newBird;
}

void BirdUpdate(Bird *bird, float dt) {
  bird->dy += GRAVITY * dt;
  bird->y += bird->dy;
}

void BirdDraw(Bird *bird) {
  DrawTexture(bird->birdImg, bird->x, bird->y, WHITE);
}
