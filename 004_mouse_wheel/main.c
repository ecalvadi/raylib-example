/**
 *
 * Drawing a screen with a square, the square is controlled 
 * by the mouse wheel.
 *
 * */

#include <raylib.h>

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Input Mouse Wheel");

    //Starting position and speed 
    int boxPositionY = screenHeight / 2 - 40;
    int scrollSpeed = (fps == 60) ? 4 : 8;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        //box position by multiply the mouse wheel by scroll speed 
        //(the mouse wheel take a positive or negative value)
        boxPositionY -= ( GetMouseWheelMove() * scrollSpeed );

        //if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ToggleFullscreen();

        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(DARKGRAY);

        //Draw a rectangle
        //Position X, Y, width, heigh, Color
        DrawRectangle( screenWidth / 2 - 40, boxPositionY, 80, 80, RAYWHITE);

        //Drawing a text on the screen, passing text, then position x and y,
        //then the size and finally the color.
        DrawText(
            "Use the mouse wheel to move the cube up and down!", 
            10, 10, 20, RAYWHITE);

        DrawText(
            FormatText("Box position Y: %03i", boxPositionY),
            10, 40, 20, LIGHTGRAY);

	DrawFPS(0, 0);

        EndDrawing();
    }

    //Clear
    CloseWindow();

    return 0;
}

