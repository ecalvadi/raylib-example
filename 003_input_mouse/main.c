/**
 *
 * Drawing a screen with a circle, the circle is controlled 
 * by the mouse.
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

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Mouse Input");

    //Initialization of the ball object in the center of the screen 
    Vector2 ballPosition; //Initialization on the game loop

    //Seteamos una variable color
    Color ballColor = LIGHTGRAY;

    //If FPS are 60, the velocity is 2.0, if are other, like 30 FPS, 
    //the velocity is 4.0 (we need more velocity in contrast of fewer 
    //frames to move at the same speed)
    //float velocity = (fps == 60) ? 2.0f : 4.0f;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        ballPosition = GetMousePosition();

        //Capture mouse events (click)
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ballColor = MAROON;
        else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) ballColor = LIME;
        else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) ballColor = LIGHTGRAY;

        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(DARKGRAY);

        //Drawing a text on the screen, passing text, then position x and y,
        //then the size and finally the color.
        DrawText(
            "Move the ball with the mouse, and change the color with mouse buttons", 
            10, 10, 20, RAYWHITE);

        //Draw the circle, in the position vector2, the size and finally a color.
        DrawCircleV(ballPosition, 40, ballColor);

	DrawFPS(0, 0);

        EndDrawing();
    }

    //Clear
    CloseWindow();

    return 0;
}

