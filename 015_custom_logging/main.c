/**
 *
 * This example show how work logging 
 *
 * */

#include <raylib.h>

#include <stdio.h>  //Required for: fopen(), fclose(), fputc(), fwrite(), printf(), fprintf(), funopen()
#include <time.h>   //Required for: time_t, tm, time(), localtime(), strftime()

//Custom logging function 
void LogCustom(int msgType, const char *text, va_list args);

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //First thing we do is setting our custom logger to ensure everything raylib logs
    //will use our own logger isntead of its internal one
    SetTraceLogCallback(LogCustom);

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D Custom Logging");

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop


        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          DrawText("Check out the console output to see the custom logger in action!", 320, 350, 20, LIGHTGRAY);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

//Implementation of Custom logging function 
void LogCustom(int msgType, const char *text, va_list args)
{
  char timeStr[64] = { 0 };
  time_t now = time(NULL);
  struct tm *tm_info = localtime(&now);

  strftime( timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info );
  printf("[%s] ", timeStr);

  switch( msgType )
  {
    case LOG_INFO: printf("[INFO] : "); break;
    case LOG_ERROR: printf("[ERROR]: "); break;
    case LOG_WARNING: printf("[WARN] : "); break;
    case LOG_DEBUG: printf("[DEBUG]: "); break;
    default: break;
  }

  vprintf( text, args );
  printf("\n");
}
