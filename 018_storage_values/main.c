/**
 *
 * This example save/load values from storage, like Scores 
 *
 * */

#include <raylib.h>

//NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum {
  STORAGE_POSITION_SCORE    = 0,
  STORAGE_POSITION_HISCORE  = 1
} StorageData;

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Storage save/load values");

    int score = 0;
    int hiscore = 0;
    int framesCounter = 0;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        if( IsKeyPressed(KEY_R) )
        {
          score = GetRandomValue(1000, 2000);
          hiscore = GetRandomValue(2000, 4000);
        }

        if( IsKeyPressed(KEY_ENTER) )
        {
          SaveStorageValue(STORAGE_POSITION_SCORE, score);
          SaveStorageValue(STORAGE_POSITION_HISCORE, hiscore);
        }
        else if( IsKeyPressed(KEY_SPACE) )
        {
          //NOTE: If requested position could not be found, value 0 is returned
          score = LoadStorageValue(STORAGE_POSITION_SCORE);
          hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
        }

        framesCounter++;

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          DrawText( TextFormat("SCORE: %i", score), 540, 230, 40, MAROON);
          DrawText( TextFormat("HI-SCORE: %i", hiscore), 480, 340, 50, BLACK);

          DrawText( TextFormat("frames: %i", framesCounter), 10, 10, 20, LIME);

          DrawText( TextFormat("Press R to generate random numbers"), 450, 280, 20, LIGHTGRAY);
          DrawText( TextFormat("Press ENTER to SAVE values"), 480, 510, 20, LIGHTGRAY);
          DrawText( TextFormat("Press SPACE to LOAD values"), 482, 550, 20, LIGHTGRAY);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

