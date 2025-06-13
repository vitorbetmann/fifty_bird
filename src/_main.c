// Includes
// --------
#include "Assets_paths.h"
#include "Bird.h"
#include "Pipe.h"
#include "PipePairManager.h"
#include "Settings.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>
// --------

// Prototypes
// ----------
// Init funcitons
void GameInit(void);
void LoadImages(void);

// Run functions
void GameRun(void);

void UpdateAll(float dt);
void UpdateBG(float dt);
void UpdateGround(float dt);

void DrawAll(void);
void DrawOnVScreen(void);
void DrawOnWindow(void);

// Unload functions
void GameUnload(void);
void UnloadImages(void);
// ----------

// Varaiables
// ----------
float bgScroll = 0, groundScroll = 0;
static RenderTexture2D vScreen;
static Texture2D bgImg, groundImg;
static Bird *bird;
Pipe *testPipe;
PipePairQueue pipes;
// ----------

// Let's have fun!
// ---------------
int main(void) {
  GameInit();
  GameRun();
  GameUnload();
}
// ---------------

// Init functions
// --------------
void GameInit(void) {
  // Window congfig
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(window.x, window.y, "Fifty Bird");
  vScreen = LoadRenderTexture(V_SCREEN.x, V_SCREEN.y);
  SetTextureFilter(vScreen.texture, TEXTURE_FILTER_POINT);
  SetTargetFPS(TARGET_FPS);

  SetRandomSeed(time(NULL));
  // Load stuff
  LoadImages();
  PipePairManagerInit();

  bird = NewBird(V_SCREEN);
}

void LoadImages(void) {
  bgImg = LoadTexture(BG_IMG);
  groundImg = LoadTexture(GROUND_IMG);
}
// --------------

// Run functions
// -------------
void GameRun(void) {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Input
    UpdateAll(dt);
    DrawAll();
  }
}

void UpdateAll(float dt) {
  UpdateBG(dt);
  UpdateGround(dt);
  PipesUpdate(&pipes, dt, V_SCREEN);
  BirdUpdate(bird, dt);
}

void UpdateBG(float dt) {
  bgScroll -= BG_SCROLL_SPEED * dt;
  bgScroll = fmodf(bgScroll, BG_LOOPING_POINT);
}

void UpdateGround(float dt) {
  groundScroll -= GROUND_SCROLL_SPEED * dt;
  groundScroll = fmodf(groundScroll, GROUND_SCROLL_SPEED);
}

void DrawAll(void) {
  DrawOnVScreen();
  DrawOnWindow();
}

void DrawOnVScreen(void) {
  BeginTextureMode(vScreen);
  ClearBackground(BLACK);
  DrawTexture(bgImg, bgScroll, 0, WHITE);
  PipePairsDraw(&pipes);
  DrawTexture(groundImg, groundScroll, V_SCREEN.y - groundImg.height, WHITE);
  BirdDraw(bird);

  DrawFPS(10, 10);

  EndTextureMode();
}

void DrawOnWindow(void) {
  BeginDrawing();
  Rectangle source = {0, 0, V_SCREEN.x, -V_SCREEN.y};
  Rectangle dest = {0, 0, window.x, window.y};
  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  EndDrawing();
}
// -------------

// Unload functions
// ----------------
void GameUnload(void) { UnloadImages(); }

void UnloadImages(void) {
  UnloadTexture(bgImg);
  UnloadTexture(groundImg);
  PipePairsUnload(&pipes);
  PipeUnloadSprite();
}
// ----------------
