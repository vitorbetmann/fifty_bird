// --------
// Includes
// --------
#include "Bird.h"
#include <math.h>
#include <raylib.h>

// ----------
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
// Window & Screen
const int V_WIDTH = 512;
const int V_HEIGHT = 288;
const int BG_SCROLL_SPEED = 30, GROUND_SCROLL_SPEED = 60;
const int BG_LOOPING_POINT = 413, GROUND_LOOPING_POINT = V_WIDTH;
float bgScroll = 0, groundScroll = 0;
int window_width = 1280, window_height = 720;
RenderTexture2D vScreen;

// Assets
const char *const BG_IMG = "./assets/background.png";
const char *const GROUND_IMG = "./assets/ground.png";
Texture2D bgImg, groundImg;
Bird *bird;

// ---------------
// Let's have fun!
// ---------------
int main(void) {
  GameInit();
  GameRun();
  GameUnload();
}

// --------------
// Init functions
// --------------
void GameInit(void) {
  // Window congfig
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(window_width, window_height, "Fifty Bird");
  vScreen = LoadRenderTexture(V_WIDTH, V_HEIGHT);
  // SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);

  // Load stuff
  LoadImages();

  bird = BirdInit((Vector2){V_WIDTH, V_HEIGHT});
}

void LoadImages(void) {
  bgImg = LoadTexture(BG_IMG);
  groundImg = LoadTexture(GROUND_IMG);
}

// -------------
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
  DrawTexture(groundImg, groundScroll, V_HEIGHT - groundImg.height, WHITE);
  BirdDraw(bird);
  EndTextureMode();
}

void DrawOnWindow(void) {
  BeginDrawing();
  Rectangle source = {0, 0, V_WIDTH, -V_HEIGHT};
  Rectangle dest = {0, 0, window_width, window_height};
  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  EndDrawing();
}

// ----------------
// Unload functions
// ----------------
void GameUnload(void) { UnloadImages(); }

void UnloadImages(void) {
  UnloadTexture(bgImg);
  UnloadTexture(groundImg);
}
