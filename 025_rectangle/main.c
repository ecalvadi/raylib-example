/**
 *This example show a texture texture loading and drawing a part defined by a rectangle
 *
 * */

#include <raylib.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Texture Rectangle");

    //NOTE: Textures MUST be loaded after window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/scarfy.png");     //Texture loading

    Vector2 position = { 550.0f, 480.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;        //Number of spritesheet frames shown per second

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop 
        framesCounter++;

        if( framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if( currentFrame > 5 ) currentFrame = 0;
            frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
        }

        if( IsKeyPressed(KEY_RIGHT) ) framesSpeed++;
        else if( IsKeyPressed(KEY_LEFT) ) framesSpeed--;

        if( framesSpeed > MAX_FRAME_SPEED ) framesSpeed = MAX_FRAME_SPEED;
        else if( framesSpeed < MIN_FRAME_SPEED ) framesSpeed = MIN_FRAME_SPEED;

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          DrawTexture(scarfy, 290, 40, WHITE);
          DrawRectangleLines(290, 40, scarfy.width, scarfy.height, LIME);
          DrawRectangleLines(290 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);

          DrawText("FRAME SPEED: ", 365, 210, 10, DARKGRAY);
          DrawText(TextFormat("%02i FPS", framesSpeed), 875, 210, 10, DARKGRAY);
          DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 520, 240, 10, DARKGRAY);

          for(int i = 0; i < MAX_FRAME_SPEED; i++)
          {
              if( i < framesSpeed ) DrawRectangle(500 + 21 * i, 205, 20, 20, RED);
              DrawRectangleLines(500 + 21 * i, 205, 20, 20, MAROON);
          }

          DrawTextureRec(scarfy, frameRec, position, WHITE);        //Draw part of the texture
          DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);


          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

