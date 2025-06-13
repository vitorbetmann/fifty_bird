#include "raylib.h"

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdSprite;
  int birdWidth, birdHeight;
  Vector2 pos;
  float dy, rotation;
} Bird;

// ----------
// Prototypes
// ----------
Bird *NewBird(Vector2 screen);
void BirdUpdate(Bird *bird, float dt);
bool canJump(void);
void BirdDraw(Bird *bird);