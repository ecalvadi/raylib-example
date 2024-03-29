/**
 *
 * Drawing a simple window With a title and a Text inside of the window
 *
 **/

//Importing main library "raylib"
#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

int main(void) {
    //Initialization of screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;

    //Initialization of the main windows, passing the screen 
    //width and height constants, finally we added a title of the screen.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Hello World");

    //Set Frames per second (FPS)
    SetTargetFPS(60);

    //This is the Main loop of the Game
    while (!WindowShouldClose())
    {
        //TODO: Update variables of the game loop here


        //Start Drawing
        BeginDrawing();

        //Paint the background with a darkgray color
        ClearBackground(DARKGRAY);

        //Drawing a text, passing a text, then the position X and Y, finally a color
        DrawText("Bienvenido a Ñir Engine 0.1 ALPHA", 340, 300, 30, RAYWHITE);

	//DRAW CURRENT FPS
	DrawFPS(0, 0);

        //End the trawing pipeline
        EndDrawing();
    }

    //Clone windows and OpenGL
    CloseWindow();

    return 0;
}

