#include "raylib.h"

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdSprite;
  int width, height;
  Vector2 pos;
  float dy, rotation;
  Rectangle hitBox;
} Bird;

// ----------
// Prototypes
// ----------
Bird *NewBird(Vector2 screen);
void BirdUpdate(Bird *bird, float dt);
void BirdDraw(Bird *bird);