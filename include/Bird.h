#include "raylib.h"

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdImg;
  int birdWidth, birdHeight;
  Vector2 pos;
  float dy, rotation;
} Bird;

// ----------
// Prototypes
// ----------
Bird *BirdInit(Vector2 screen);
void BirdUpdate(Bird *bird, float dt);
bool canJump(void);
void BirdDraw(Bird *bird);