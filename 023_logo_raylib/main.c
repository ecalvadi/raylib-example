/**
 *This example show a texture with the RayLib Logo 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Texture Loading and Drawing");

    //NOTE: Textures MUST be loaded afer window initialization (OpenGL context is required)
    Texture2D texture = LoadTexture("resources/raylib_logo.png");

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop 
        
        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);

          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);

    //Clear
    CloseWindow();

    return 0;
}

