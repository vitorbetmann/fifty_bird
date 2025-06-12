#include "raylib.h"

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdImg;
  int birdWidth, birdHeight;
  float x, y, dy;
} Bird;

// ----------
// Prototypes
// ----------
Bird *BirdInit(Vector2 screen);
void BirdUpdate(Bird *bird, float dt);
void BirdDraw(Bird *bird);