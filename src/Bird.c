#include "Bird.h"

const char *const BIRD_IMG = "./assets/bird.png";

Bird *BirdInit(Vector2 screen) {
  static Bird newBird;
  newBird.birdImg = LoadTexture(BIRD_IMG);
  newBird.birdWidth = newBird.birdImg.width;
  newBird.birdHeight = newBird.birdImg.height;
  newBird.x = (screen.x - newBird.birdWidth) / 2;
  newBird.y = (screen.y - newBird.birdHeight) / 2;

  return &newBird;
}

void BirdUpdate(Bird *bird, Vector2 screen) {}

void BirdDraw(Bird *bird) {
  DrawTexture(bird->birdImg, bird->x, bird->y, WHITE);
}
