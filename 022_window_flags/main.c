/**
 *This example show differents Window Flags 
 *
 * */

#include <raylib.h>

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    //const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Supported Window Flags
    /*
    FLAG_VSYNC_HINT
    FLAG_FULLSCREEN_MODE            //Not working properly -> wrong scaling!
    FLAG_WINDOW_RESIZABLE
    FLAG_WINDOW_UNDECORATED
    FLAG_WINDOW_TRANSPARENT
    FLAG_WINDOW_HIDDEN
    FLAG_WINDOW_MINIMIZED           //Not supported on window creation
    FLAG_WINDOW_MAXIMIZED           //Not supported on window creation
    FLAG_WINDOW_UNFOCUSED
    FLAG_WINDOW_TOPMOST
    FLAG_WINDOW_HIGHDPI             //Errors after minimize-resize, fb size is recalculated
    FLAG_WINDOW_ALWAYS_RUN
    FLAG_MSAA_4x_HINT
    */

    //Set configuration flags for window creation
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Window Flags");

    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2};
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;

    int framesCounter = 0;

    //Set Frames per second
    //SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop 
        if( IsKeyPressed(KEY_F) ) ToggleFullscreen(); //modifies window size when scaling! 

        if( IsKeyPressed(KEY_R) )
        {
          if( IsWindowState(FLAG_WINDOW_RESIZABLE) ) ClearWindowState(FLAG_WINDOW_RESIZABLE);
          else SetWindowState(FLAG_WINDOW_RESIZABLE);
        }

        if( IsKeyPressed(KEY_D) )
        {
          if( IsWindowState(FLAG_WINDOW_UNDECORATED) ) ClearWindowState(FLAG_WINDOW_UNDECORATED);
          else SetWindowState(FLAG_WINDOW_RESIZABLE);
        }
        
        if( IsKeyPressed(KEY_H) )
        {
          if( !IsWindowState(FLAG_WINDOW_HIDDEN) ) SetWindowState(FLAG_WINDOW_HIDDEN);

          framesCounter = 0;
        }

        if( IsWindowState(FLAG_WINDOW_HIDDEN) )
        {
          framesCounter++;
          if( framesCounter >= 240 ) ClearWindowState(FLAG_WINDOW_HIDDEN); //Show window after 3 seconds
        }

        if( IsKeyPressed(KEY_N) )
        {
          if( !IsWindowState(FLAG_WINDOW_MINIMIZED) ) MinimizeWindow();

          framesCounter = 0;
        }

        //M: FLAG_WINDOW_MAXIMIZED 
        if( IsKeyPressed(KEY_M) )
        {
          if( IsWindowState(FLAG_WINDOW_MAXIMIZED) ) RestoreWindow();
          else MaximizeWindow();
        }
        //U: FLAG_WINDOW_UNFOCUSED
        if( IsKeyPressed(KEY_U) )
        {
          if( IsWindowState(FLAG_WINDOW_UNFOCUSED) ) ClearWindowState(FLAG_WINDOW_UNFOCUSED);
          else SetWindowState(FLAG_WINDOW_UNFOCUSED);
        }
        //T: FLAG_WINDOW_TOPMOST
        if( IsKeyPressed(KEY_T) )
        {
          if( IsWindowState(FLAG_WINDOW_TOPMOST) ) ClearWindowState(FLAG_WINDOW_TOPMOST);
          else SetWindowState(FLAG_WINDOW_TOPMOST);
        }
        //A: FLAG_WINDOW_ALWAYS_RUN
        if( IsKeyPressed(KEY_A) ) 
        {
          if( IsWindowState(FLAG_WINDOW_ALWAYS_RUN) ) ClearWindowState(FLAG_WINDOW_ALWAYS_RUN);
          else SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
        }
        //V: FLAG_VSYNC_HINT
        if( IsKeyPressed(KEY_V) ) 
        {
          if( IsWindowState(FLAG_VSYNC_HINT) ) ClearWindowState(FLAG_VSYNC_HINT);
          else SetWindowState(FLAG_VSYNC_HINT);
        }
 
        //Bouncing ball logic
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
        if( (ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius) ) ballSpeed.x *= -1.0f;
        if( (ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius) ) ballSpeed.y *= -1.0f;

        //StartDrawing
        BeginDrawing();

          if( IsWindowState(FLAG_WINDOW_TRANSPARENT) ) ClearBackground(BLANK);
          else ClearBackground(RAYWHITE);

          DrawCircleV(ballPosition, ballRadius, MAROON);
          DrawRectangleLinesEx( (Rectangle){ 0, 0, screenWidth, screenHeight }, 4, RAYWHITE );

          DrawCircleV(GetMousePosition(), 10, DARKBLUE);

          DrawText( FormatText("Screen Size: [%i, %i]", GetScreenWidth(), GetScreenHeight()), 10, 40, 10, GREEN);
          
          //Draw window state info
          DrawText( "Following flags can be set after window creation:", 10, 60, 10, GRAY );

          if( IsWindowState(FLAG_FULLSCREEN_MODE) ) DrawText("[F] FLAG_FULLSCREEN_MODE: on", 10, 80, 10, LIME );
          else DrawText("[F] FLAG_FULLSCREEN_MODE: off", 10, 80, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_RESIZABLE) ) DrawText("[R] FLAG_RESIZABLE: on", 10, 100, 10, LIME );
          else DrawText("[R] FLAG_WINDOW_RESIZABLE: off", 10, 100, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_UNDECORATED) ) DrawText("[D] FLAG_WINDOW_UNDECORATED: on", 10, 120, 10, LIME );
          else DrawText("[D] FLAG_WINDOW_UNDECORATED: off", 10, 120, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_HIDDEN) ) DrawText("[H] FLAG_WINDOW_HIDDEN: on", 10, 140, 10, LIME );
          else DrawText("[H] FLAG_WINDOW_HIDDEN: off", 10, 140, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_MINIMIZED) ) DrawText("[N] FLAG_WINDOW_MINIMIZED: on", 10, 160, 10, LIME );
          else DrawText("[N] FLAG_WINDOW_MINIMIZED: off", 10, 160, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_MAXIMIZED) ) DrawText("[M] FLAG_WINDOW_MAXIMIZED: on", 10, 180, 10, LIME );
          else DrawText("[M] FLAG_WINDOW_MAXIMIZED: off", 10, 180, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_UNFOCUSED) ) DrawText("[G] FLAG_WINDOW_UNFOCUSED: on", 10, 200, 10, LIME );
          else DrawText("[G] FLAG_WINDOW_UNFOCUSED: off", 10, 200, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_TOPMOST) ) DrawText("[T] FLAG_WINDOW_TOPMOST: on", 10, 220, 10, LIME );
          else DrawText("[T] FLAG_WINDOW_TOPMOST: off", 10, 220, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_ALWAYS_RUN) ) DrawText("[A] FLAG_WINDOW_ALWAYS_RUN: on", 10, 240, 10, LIME );
          else DrawText("[A] FLAG_WINDOW_ALWAYS_RUN: off", 10, 240, 10, MAROON);

          if( IsWindowState(FLAG_VSYNC_HINT) ) DrawText("[V] FLAG_VSYNC_HINT: on", 10, 260, 10, LIME );
          else DrawText("[V] FLAG_VSYNC_HINT: off", 10, 260, 10, MAROON);

          DrawText("Following flags can only be set before window creation: ", 10, 300, 10, GRAY);
          if( IsWindowState(FLAG_WINDOW_HIGHDPI) ) DrawText("FLAG_WINDOW_HIGHDPI: on", 10, 320, 10, LIME );
          else DrawText("FLAG_WINDOW_HIGHDPI: off", 10, 320, 10, MAROON);

          if( IsWindowState(FLAG_WINDOW_TRANSPARENT) ) DrawText("FLAG_WINDOW_TRANSPARENT: on", 10, 340, 10, LIME );
          else DrawText("FLAG_WINDOW_TRANSPARENT: off", 10, 340, 10, MAROON);

          if( IsWindowState(FLAG_MSAA_4X_HINT) ) DrawText("FLAG_MSAA_4X_HINT: on", 10, 360, 10, LIME );
          else DrawText("FLAG_MSAA_4X_HINT: off", 10, 360, 10, MAROON);

          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

