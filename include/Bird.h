#include "raylib.h"

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdImg;
  int birdWidth, birdHeight;
  float x, y;
} Bird;

// ----------
// Prototypes
// ----------
Bird *BirdInit(Vector2 screen);
void BirdUpdate(Bird *bird, Vector2 screen);
void BirdDraw(Bird *bird);

// ---------
// Variables
// ---------
extern const char *const BIRD_IMG;