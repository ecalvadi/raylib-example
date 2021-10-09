/**
 *
 * This example generates random values every 2 seconds
 *
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Generate Random values");

    int framesCounter = 0;  //Variable uset to count frames 

    int randValue = GetRandomValue(-8, 5); //Get a random integer number between -8 and 5 (both included)

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        framesCounter++;

        //Every two seconds (120 frames) a new random value is generated
        if( ((framesCounter / 120) % 2) == 1 )
        {
          randValue = GetRandomValue( -8, 5 );
          framesCounter = 0;
        }

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          DrawText("Every 2 seconds a new random value is generated: ", 400, 300, 20, MAROON);

          DrawText( TextFormat("%i", randValue), 640, 380, 80, LIGHTGRAY );


        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

