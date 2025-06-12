// Includes
// --------
#include "Assets_paths.h"
#include "Bird.h"
#include <math.h>
#include <raylib.h>
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
Vector2 window = {1280, 720};
const Vector2 V_SCREEN = {512, 288};

const int BG_SCROLL_SPEED = 30, GROUND_SCROLL_SPEED = 60;
const int BG_LOOPING_POINT = 413, GROUND_LOOPING_POINT = V_SCREEN.x;

float bgScroll = 0, groundScroll = 0;

RenderTexture2D vScreen;
Texture2D bgImg, groundImg;
Bird *bird;
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
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(window.x, window.y, "Fifty Bird");
  vScreen = LoadRenderTexture(V_SCREEN.x, V_SCREEN.y);
  // SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);

  // Load stuff
  LoadImages();

  bird = BirdInit(V_SCREEN);
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
  DrawTexture(groundImg, groundScroll, V_SCREEN.y - groundImg.height, WHITE);
  BirdDraw(bird);
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
}
// ----------------
