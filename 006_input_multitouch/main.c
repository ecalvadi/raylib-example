/**
 *
 * This example show a five circles that react to a touch, supporting
 * touch every circle at the same time.
 *
 * */

#include <raylib.h>

#define MAX_TOUCH_POINTS 10

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Input Multitouch");

    //Set the position of a ball
    Vector2 ballPosition;// = { -100.0f, -100.0f };
    Color ballColor = BEIGE;

    //Initialization of touch counter and position
    int touchCounter = 0;
    Vector2 touchPosition;// = { 0 };

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        ballPosition = GetMousePosition();

        ballColor = BEIGE;

        if( IsMouseButtonDown(MOUSE_LEFT_BUTTON) ) ballColor = MAROON;
        if( IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) ) ballColor = LIME;
        if( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ) ballColor = DARKBLUE;

        if( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) touchCounter = 10;
        if( IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON) ) touchCounter = 10;
        if( IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) ) touchCounter = 10;

        if( touchCounter > 0 ) touchCounter--;

        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(RAYWHITE);

        //Multitouch 
        for( int i = 0; i < MAX_TOUCH_POINTS; ++i)
        {
          //Gett the touch point
          touchPosition = GetTouchPosition(i);

          //Make sure that point is not (-1, -1) as this means there is no touch for it
          if( (touchPosition.x >= 0) && (touchPosition.y >= 0) )
          {
            //Draw circle and touch index number
            DrawCircleV(touchPosition, 34, ORANGE);
            DrawText( TextFormat("%d", i), (int)touchPosition.x - 10, (int)touchPosition.y - 70, 40, BLACK);
          }
        }

        //Draw the normal mouse location 
        DrawCircleV(ballPosition, (float)(30 + (touchCounter*3)), ballColor);

        DrawText("Move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);
        DrawText("Touch the screen at multiple locations to get multiple balls", 10, 30, 20, DARKGRAY);

        DrawFPS(0, 0);


        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

