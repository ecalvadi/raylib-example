/**
 *
 * This example detect the gestures of touching screen (mouse or touch) 
 * and show the stack of actions detected.
 *
 * */

#include <raylib.h>
#include <string.h>

#define MAX_GESTURE_STRINGS 30

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Input Gestures");

    //Set the touchPosition and area of detection
    Vector2 touchPosition = {0, 0};
    Rectangle touchArea = { 220, 10, screenWidth - 230, screenHeight - 20 };

    //Init gestures 
    int gesturesCount = 0;
    char gestureStrings[MAX_GESTURE_STRINGS][32];

    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    //SetGesturesEnabled(0b0000000000001001); //Enable only some gestures to be detected 

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();
        touchPosition = GetTouchPosition(0);

        //Check Collision and gesture
        if( CheckCollisionPointRec(touchPosition, touchArea) && (currentGesture != GESTURE_NONE) )
        {
          //if the currentGesture are "new" then do something
          if( currentGesture != lastGesture )
          {
            //Store gesture String 
            switch(currentGesture)
            {
              case GESTURE_TAP: strcpy( gestureStrings[gesturesCount], "GESTURE TAP" ); break;
              case GESTURE_DOUBLETAP: strcpy( gestureStrings[gesturesCount], "GESTURE DOUBLETAP" ); break;
              case GESTURE_HOLD: strcpy( gestureStrings[gesturesCount], "GESTURE HOLD" ); break;
              case GESTURE_DRAG: strcpy( gestureStrings[gesturesCount], "GESTURE DRAG" ); break;
              case GESTURE_SWIPE_RIGHT: strcpy( gestureStrings[gesturesCount], "GESTURE SWIPE RIGHT" ); break;
              case GESTURE_SWIPE_LEFT: strcpy( gestureStrings[gesturesCount], "GESTURE SWIPE LEFT" ); break;
              case GESTURE_SWIPE_UP: strcpy( gestureStrings[gesturesCount], "GESTURE SWIPE UP" ); break;
              case GESTURE_SWIPE_DOWN: strcpy( gestureStrings[gesturesCount], "GESTURE SWIPE DOWN" ); break;
              case GESTURE_PINCH_IN: strcpy( gestureStrings[gesturesCount], "GESTURE PINCH IN" ); break;
              case GESTURE_PINCH_OUT: strcpy( gestureStrings[gesturesCount], "GESTURE PINCH OUT" ); break;
              default: break;
            }

            gesturesCount++;

            //Reset gestures strings 
            if( gesturesCount >= MAX_GESTURE_STRINGS)
            {
              for( int i = 0; i < MAX_GESTURE_STRINGS; i++ ) strcpy(gestureStrings[i], "\0");

              gesturesCount = 0;
            }
          }
        }

        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(RAYWHITE);

        //Draw gestures area
        DrawRectangleRec(touchArea, GRAY);
        DrawRectangle(225, 15, screenWidth - 240, screenHeight - 30, RAYWHITE);

        DrawText("GESTURES TEST AREA", screenWidth - 270, screenHeight - 40, 20, Fade(GRAY, 0.5f));

        //Create rectangles and text of pressed gestures
        //the last text are maroon
        for( int i = 0; i < gesturesCount; i++ )
        {
          if( i%2 == 0 ) DrawRectangle(10, 30 + 20 * i, 200, 20, Fade(LIGHTGRAY, 0.5f));
          else DrawRectangle(10, 30 + 20 * i, 200, 20, Fade(LIGHTGRAY, 0.3f));

          if( i < gesturesCount - 1 ) DrawText(gestureStrings[i], 35, 36 + 20 * i, 10, DARKGRAY);
          else DrawText(gestureStrings[i], 35, 36 + 20 * i, 10, MAROON);
        }

        //Draw border rectangle for gestures log
        DrawRectangleLines(10, 29, 200, screenHeight - 50, GRAY);
        DrawText("DETECTED GESTURES", 50, 15, 10, GRAY);

        //Show circleV while gesture is in action 
        if( currentGesture != GESTURE_NONE ) DrawCircleV(touchPosition, 30, MAROON);

        DrawFPS(0, 0);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

