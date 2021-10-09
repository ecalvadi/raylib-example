/**
 *
 * This example of scissors test 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Scissors Test");

    Rectangle scissorArea = { 0, 0, 300, 300 };
    bool scissorMode = true;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        if( IsKeyPressed(KEY_S) ) scissorMode = !scissorMode;

        //Centre the scissor area aroind the mouse position
        scissorArea.x = (float)GetMouseX() - scissorArea.width / 2;
        scissorArea.y = (float)GetMouseY() - scissorArea.height / 2;

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          if( scissorMode ) BeginScissorMode( (int)scissorArea.x, (int)scissorArea.y, (int)scissorArea.width, (int)scissorArea.height );

          //Draw full screen rectangle and some text
          //NOTE: Only part defined by scissor area will be rendered
          DrawRectangle( 0, 0, screenWidth, screenHeight, RED);
          DrawText("Move the mouse aroun to reveal this text!", 590, 400, 20, LIGHTGRAY);

          if( scissorMode ) EndScissorMode();

          DrawRectangleLinesEx( scissorArea, 1, BLACK );
          DrawText("Press S to toggle scrissor test", 10, 10, 20, BLACK );

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

