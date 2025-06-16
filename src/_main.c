// Includes
// --------
#include "Assets_paths.h"
#include "Pipe.h"
#include "Settings.h"
#include "states/StatePlay.h"
#include "states/StateScore.h"
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

void CheckGameState(void);
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
static Bird *bird;

static float bgScroll = 0, groundScroll = 0;
static RenderTexture2D vScreen;
static Texture2D bgImg, groundImg;

static GameState currGameState;
static void (*CurrStateUpdate)(float dt);
static void (*CurrStateDraw)();
static void (*CurrStateExit)();

Font smallFont, mediumFont, flappyFont, hugeFont;
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
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(window.x, window.y, GAME_TITLE);
  vScreen = LoadRenderTexture(V_SCREEN.x, V_SCREEN.y);
  SetTargetFPS(TARGET_FPS);

  SetRandomSeed(time(NULL));

  // Load stuff
  LoadImages();
  LoadFonts();

  bird = NewBird(V_SCREEN);

  // Let us begin
  ChangeCurrState(TITLE);
}

void LoadImages(void) {
  bgImg = LoadTexture(BG_IMG);
  groundImg = LoadTexture(GROUND_IMG);
}

void LoadFonts(void) {
  smallFont = LoadFont(FONT_REGULAR);
  mediumFont = hugeFont = flappyFont = LoadFont(FONT_FLAPPY);

  SetTextureFilter(smallFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(mediumFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(hugeFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(flappyFont.texture, TEXTURE_FILTER_POINT);
}
// --------------

// Run functions
// -------------
void GameRun(void) {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    CheckGameState();
    UpdateAll(dt);
    DrawAll();
  }
}

void CheckGameState() {
  switch (currGameState) {
  case TITLE:
    if (IsKeyPressed(KEY_ENTER)) {
      ChangeCurrState(PLAY);
    }
    break;
  case COUNTDOWN:
    break;
  case PLAY:
    if (!bird->isAlive) {
      ChangeCurrState(SCORE);
    }
    break;
  case SCORE:
    if (IsKeyPressed(KEY_ENTER)) {
      ChangeCurrState(PLAY);
    }
    break;
  default:
    break;
  }
}

void ChangeCurrState(GameState state) {
  switch (state) {
  case TITLE:
    currGameState = TITLE;

    StateTitleEnter(bird);

    CurrStateDraw = StateTitleDraw;
    CurrStateUpdate = StateTitleUpdate;
    CurrStateExit = StateTitleExit;
    break;
  case COUNTDOWN:
    break;
  case PLAY:
    CurrStateExit();
    currGameState = PLAY;

    StatePlayEnter(bird);

    CurrStateDraw = StatePlayDraw;
    CurrStateUpdate = StatePlayUpdate;
    CurrStateExit = StatePlayExit;
    break;
  case SCORE:
    CurrStateExit();
    currGameState = SCORE;

    StateScoreEnter(bird);

    CurrStateDraw = StateScoreDraw;
    CurrStateUpdate = StateScoreUpdate;
    CurrStateExit = StateScoreExit;
    break;
  default:
    break;
  }
}

void UpdateAll(float dt) {
  BGUpdate(dt);
  CurrStateUpdate(dt);
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
  CurrStateDraw();
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

void UnloadFonts(void) {
  UnloadFont(smallFont);
  UnloadFont(flappyFont);
}

void UnloadSounds(void) {}
// ----------------
