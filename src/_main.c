// Includes
// --------
#include "Assets_paths.h"
#include "Pipe.h"
#include "Settings.h"
#include "states/StatePlay.h"
#include "states/StateTitle.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>
// --------

// Data types
typedef enum {
  TITLE,
  COUNTDOWN,
  PLAY,
  SCORE,
} GameState;

// Prototypes
// ----------
// Init funcitons
void GameInit(void);
void LoadImages(void);
void LoadFonts(void);

// Run functions
void GameRun(void);

void GetInput(void);
void ChangeCurrState(GameState state);

void UpdateAll(float dt);
void BGUpdate(float dt);
void GroundUpdate(float dt);

void DrawAll(void);
void DrawOnVScreen(void);
void DrawOnWindow(void);

// Unload functions
void GameUnload(void);
void UnloadImages(void);
void UnloadFonts(void);
void UnloadSounds(void);
// ----------

// Varaiables
// ----------
static float bgScroll = 0, groundScroll = 0;
static RenderTexture2D vScreen;
static Texture2D bgImg, groundImg;

static Font smallFont, mediumFont, flappyFont, hugeFont;
static int smallFontSize, mediumFontSize, flappyFontSize, hugeFontSize;

static GameState currGameState;
static void (*UpdateCurrState)(float dt);
static void (*DrawCurrState)();
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
  SetTargetFPS(TARGET_FPS);

  SetRandomSeed(time(NULL));

  // Load stuff
  LoadImages();
  LoadFonts();

  // Let us begin
  ChangeCurrState(TITLE);
}

void LoadImages(void) {
  bgImg = LoadTexture(BG_IMG);
  groundImg = LoadTexture(GROUND_IMG);
}

void LoadFonts(void) {
  smallFont = LoadFont("./assets/font.ttf");
  smallFontSize = 8;

  mediumFont = flappyFont = hugeFont = LoadFont("./assets/flappy.ttf");
  mediumFontSize = 14;
  flappyFontSize = 28;
  hugeFontSize = 56;
}
// --------------

// Run functions
// -------------
void GameRun(void) {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    GetInput();
    UpdateAll(dt);
    DrawAll();
  }
}

void GetInput() {
  switch (currGameState) {
  case TITLE:
    if (IsKeyPressed(KEY_SPACE)) {
      ChangeCurrState(PLAY);
    }
    break;
  case COUNTDOWN:
    break;
  case PLAY:
    break;
  case SCORE:
    break;
  default:
    break;
  }
}

void ChangeCurrState(GameState state) {
  switch (state) {
  case TITLE:
    currGameState = TITLE;
    puts("you're in title now");

    StateTitleEnter();

    DrawCurrState = StateTitleDraw;
    UpdateCurrState = StateTitleUpdate;
    break;
  case COUNTDOWN:
    break;
  case PLAY:
    currGameState = PLAY;
    puts("you're in play now!");

    StatePlayEnter(StateTitleExit());

    DrawCurrState = StatePlayDraw;
    UpdateCurrState = StatePlayUpdate;
    break;
  case SCORE:
    break;
  default:
    break;
  }
}

void UpdateAll(float dt) {
  BGUpdate(dt);
  UpdateCurrState(dt);
  GroundUpdate(dt);
}

void BGUpdate(float dt) {
  bgScroll -= BG_SCROLL_SPEED * dt;
  bgScroll = fmodf(bgScroll, BG_LOOPING_POINT);
}

void GroundUpdate(float dt) {
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
  DrawCurrState();
  DrawTexture(groundImg, groundScroll, V_SCREEN.y - groundImg.height, WHITE);
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
void GameUnload(void) {
  UnloadImages();
  UnloadFonts();
  UnloadSounds();
}

void UnloadImages(void) {
  UnloadTexture(bgImg);
  UnloadTexture(groundImg);
  StatePlayExit();
  PipeUnloadSprite();
}

void UnloadFonts(void) {}
void UnloadSounds(void) {}
// ----------------
