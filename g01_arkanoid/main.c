/**
 *
 * Simple 2D Arkanoid game 
 *
 **/

//Importing main library "raylib"
#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

//Defines some game constants 
#define PLAYER_MAX_LIFE   5
#define LINES_OF_BRICKS   5
#define BRICKS_PER_LINE   20

//Types and structures definition
typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Player {
  Vector2 position;
  Vector2 size;
  int life;
} Player;

typedef struct Ball {
  Vector2 position;
  Vector2 speed;
  int radius;
  bool active;
} Ball;

typedef struct Brick {
  Vector2 position;
  bool active;
} Brick;

//Global variables declaration
static const int screenWidth = 1280;
static const int screenHeight = 720;
static const int fps = 60;


static bool gameOver = false;
static bool pause = false;

static Player player = { 0 };
static Ball ball = { 0 };
static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] = { 0 };
static Vector2 brickSize = { 0 };

//Modules functions declarations 
void InitGame(void);             //Initialize game 
void UpdateGame(void);           //Update game (by one frame)
void DrawGame(void);             //Draw Game (one frame)
void UnloadGame(void);           //Unload game
void UpdateDrawFrame(void);      //Update and Draw Frame (one frame)

int main(void) {

    //Initialization of the main windows, passing the screen 
    //width and height constants, finally we added a title of the screen.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Arkanoid");

    //Initialize Game
    InitGame();

#if defined(PLATFORM_WEB)    
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    //Set Frames per second (FPS)
    SetTargetFPS(fps);

    //This is the Main loop of the Game
    while (!WindowShouldClose())
    {
        //TODO: Update variables of the game loop here
        UpdateDrawFrame();
    }
#endif

    //Clean memory 
    UnloadGame();

    //Clone windows and OpenGL
    CloseWindow();

    return 0;
}

//Implementation of functions

//Game initialization
void InitGame(void)
{
  //Another way to get screen Width: GetScreenWidth()
  brickSize = (Vector2){ screenWidth / BRICKS_PER_LINE, 40 };

  //Initialize player
  player.position = (Vector2){ screenWidth / 2, screenHeight * 7 / 8 };
  player.size = (Vector2){ screenWidth / 10, 20 };
  player.life = PLAYER_MAX_LIFE;

  //Initialize ball
  ball.position = (Vector2){ screenWidth / 2, screenHeight * 7 / 8 - 30 };
  ball.speed = (Vector2){ 0, 0 };
  ball.radius = 7;
  ball.active = false;

  //Initialize bricks
  int initialDownPosition = 50;

  for( int i = 0; i < LINES_OF_BRICKS; i++ )
  {
    for( int j = 0; j < BRICKS_PER_LINE; j++ )
    {
      brick[i][j].position = (Vector2){ j * brickSize.x + brickSize.x / 2, i * brickSize.y + initialDownPosition };
      brick[i][j].active = true;
    }
  }
}

//Game update implementation
void UpdateGame(void)
{
  if( !gameOver )
  {
    if( IsKeyPressed(KEY_P) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT)) pause = !pause;

    if( !pause )
    {
      //Player movement logic
      if( IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) player.position.x -= 5;
      if( (player.position.x - player.size.x / 2) <= 0 ) player.position.x = player.size.x / 2;
      if( IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ) player.position.x += 5;
      if( (player.position.x + player.size.x / 2) >= screenWidth ) player.position.x = screenWidth - player.size.x / 2;

      //Ball launching logic
      if( !ball.active )
      {
        ball.active = true;
        ball.speed = (Vector2){ 0, -5 };
      }

      // Ball movement logic
      if( ball.active )
      {
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;
      }
      else
      {
        ball.position = (Vector2){ player.position.x, screenHeight * 7 / 8 - 30};
      }

      //Collision logic: ball vs walls 
      if( ((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0) ) ball.speed.x *= -1;
      if( (ball.position.y - ball.radius) <= 0 ) ball.speed.y *= -1;
      if( (ball.position.y + ball.radius) >= screenHeight )
      {
        ball.speed = (Vector2){ 0, 0 };
        ball.active = false;

        player.life--;
      }

      //Collision logic: ball vs player 
      if( CheckCollisionCircleRec(ball.position, ball.radius,
            (Rectangle){ player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y }))
      {
        if( ball.speed.y > 0)
        {
          ball.speed.y *= -1;
          ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 2) * 5;
        }
      }

      //Collision logic: ball vs bricks 
      for( int i = 0; i < LINES_OF_BRICKS; i++ )
      {
        for( int j = 0; j < BRICKS_PER_LINE; j++ )
        {
          if( brick[i][j].active )
          {
            //Hit below
            if( ((ball.position.y - ball.radius) <= (brick[i][j].position.y + brickSize.y / 2)) &&
                ((ball.position.y - ball.radius) > (brick[i][j].position.y + brickSize.y / 2 + ball.speed.y)) &&
                ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y < 0))
            {
              brick[i][j].active = false;
              ball.speed.y *= -1;
            }
            //Hit above
            else if( ((ball.position.y + ball.radius) >= (brick[i][j].position.y - brickSize.y / 2)) &&
                ((ball.position.y + ball.radius) < (brick[i][j].position.y - brickSize.y / 2 + ball.speed.y)) &&
                ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x / 2 + ball.radius * 2 / 3)) && (ball.speed.y > 0))
            {
              brick[i][j].active = false;
              ball.speed.y *= -1;
            }
            //Hit left
            else if( ((ball.position.x + ball.radius) >= (brick[i][j].position.x - brickSize.x / 2)) &&
                ((ball.position.x + ball.radius) < (brick[i][j].position.x - brickSize.x / 2 + ball.speed.x)) &&
                ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x > 0))
            {
              brick[i][j].active = false;
              ball.speed.x *= -1;
            }
            //Hit right
            else if( ((ball.position.x - ball.radius) <= (brick[i][j].position.x + brickSize.x / 2)) &&
                ((ball.position.x - ball.radius) > (brick[i][j].position.x + brickSize.x / 2 + ball.speed.x)) &&
                ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y / 2 + ball.radius * 2 / 3)) && (ball.speed.x < 0))
            {
              brick[i][j].active = false;
              ball.speed.x *= -1;
            }
          }
        }
      }

      //Game over logic 
      if( player.life <= 0) gameOver = true;
      else
      {
        gameOver = true;

        for( int i = 0; i < LINES_OF_BRICKS; i++ )
        {
          for( int j = 0; j < BRICKS_PER_LINE; j++)
          {
            if( brick[i][j].active) gameOver = false;
          }
        }
      }
    }
  }
  else
  {
    if( IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT) )
    {
      InitGame();
      gameOver = false;
    }
  }
}

//Draw function (executes every frame)
void DrawGame(void)
{
  BeginDrawing();
    
    ClearBackground(BLACK);

    if( !gameOver )
    {
      //Draw Player bar
      DrawRectangle(player.position.x - player.size.x / 2, player.position.y - player.size.y / 2, player.size.x, player.size.y, WHITE);

      //Draw player lives
      for( int i = 0; i < player.life; i++ ) DrawRectangle(20 + 40 * i, screenHeight - 30, 35, 10, LIGHTGRAY);

      //Draw ball
      DrawCircleV(ball.position, ball.radius, MAROON);

      //Draw bricks
      for( int i = 0; i < LINES_OF_BRICKS; i++ )
      {
        for( int j = 0; j < BRICKS_PER_LINE; j++ )
        {
          if( brick[i][j].active )
          {
            if( (i + j) % 2 == 0 )
            {
              DrawRectangle( brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2,
                  brickSize.x, brickSize.y, WHITE);
            }
            else 
            {
              DrawRectangle( brick[i][j].position.x - brickSize.x / 2, brick[i][j].position.y - brickSize.y / 2,
                  brickSize.x, brickSize.y, LIGHTGRAY);
            }
          }
        }
      }

      if( pause ) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, LIGHTGRAY);
    }
    else DrawText("PRESS [ENTER] OR <START> TO PLAY AGAIN", screenWidth / 2 - MeasureText("PRESS [ENTER] OR <START> TO PLAY AGAIN", 20) / 2, screenHeight / 2 - 50, 20, LIGHTGRAY);

  EndDrawing();
}

//Function to clean all the Data
void UnloadGame(void)
{
  //TODO: clean de the data
}

//Function to update the game and draw in one call
void UpdateDrawFrame(void)
{
  UpdateGame();
  DrawGame();
}


