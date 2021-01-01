/**
 *
 * Drawing a screen with a circle, the circle is controlled 
 * by the keyboard, UP, DONW, LEFT and RIGHT.
 *
 * */

#include <raylib.h>

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 30; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Input keys");

    //Initialization of the ball object in the center of the screen 
    Vector2 ballPosition = { (float) screenWidth / 2, (float) screenHeight / 2 };

    //If FPS are 60, the velocity is 2.0, if are other, like 30 FPS, 
    //the velocity is 4.0 (we need more velocity in contrast of fewer 
    //frames to move at the same speed)
    float velocity = (fps == 60) ? 2.0f : 4.0f;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        if(IsKeyDown(KEY_RIGHT)) ballPosition.x += velocity;
        if(IsKeyDown(KEY_LEFT)) ballPosition.x -= velocity;
        if(IsKeyDown(KEY_UP)) ballPosition.y -= velocity;
        if(IsKeyDown(KEY_DOWN)) ballPosition.y += velocity;
        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(DARKGRAY);

        //Drawing a text on the screen, passing text, then position x and y,
        //then the size and finally the color.
        DrawText("Move the ball with arrow keys", 10, 10, 20, RAYWHITE);

        //Draw the circle, in the position vector2, the size and finally a color.
        DrawCircleV(ballPosition, 50, LIGHTGRAY);

	DrawFPS(0, 0);

        EndDrawing();
    }

    //Clear
    CloseWindow();

    return 0;
}

