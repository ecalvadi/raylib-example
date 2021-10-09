/**
 * A paint made in Raylib 
 *
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

#define MAX_COLORS_COUNT   23    //Number of colors available

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Texture Loading and Drawing");

    //Colorus to choose from 
    Color colors[MAX_COLORS_COUNT] = {
      RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
      SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
      LIGHTGRAY, GRAY, DARKGRAY, BLACK
    };

    //Define colorsRecs data (for every rectangle)
    Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };

    for( int i = 0; i < MAX_COLORS_COUNT; i++)
    {
      colorsRecs[i].x = 10.0f + 30.0f*(float)i + 2.0f*(float)i;
      colorsRecs[i].y = 10;
      colorsRecs[i].width = 30;
      colorsRecs[i].height = 30;
    }

    int colorSelected = 0;
    int colorSelectedPrev = colorSelected;
    int colorMouseHover = 0;
    int brushSize = 20;

    Rectangle btnSaveRec = { 750, 10, 40, 30 };
    bool btnSaveMouseHover = false;
    bool showSaveMessage = false;
    int saveMessageCounter = 0;

    //Create a renderTexture to use as a canvas
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    //Clear render texture begore entering the game loop 
    BeginTextureMode(target);
    ClearBackground(colors[0]);
    EndTextureMode();

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop 
        Vector2 mousePos = GetMousePosition();

        //Move between colors with keys
        if( IsKeyPressed(KEY_RIGHT) ) colorSelected++;
        else if( IsKeyPressed(KEY_LEFT) ) colorSelected--;

        if( colorSelected >= MAX_COLORS_COUNT ) colorSelected = MAX_COLORS_COUNT -1;
        else if( colorSelected < 0 ) colorSelected = 0;

        //ChooseColor with mouse 
        for( int i = 0; i < MAX_COLORS_COUNT; i++)
        {
          if( CheckCollisionPointRec(mousePos, colorsRecs[i]) )
          {
            colorMouseHover = i;
            break;
          }
          else colorMouseHover = -1;
        }

        if( (colorMouseHover >= 0) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
        {
          colorSelected = colorMouseHover;
          colorSelectedPrev = colorSelected;
        }

        //change brush size
        brushSize += (int)GetMouseWheelMove() * 5;
        if( brushSize < 2 ) brushSize = 3;
        if( brushSize > 50 ) brushSize = 50;

        if( IsKeyPressed(KEY_C) )
        {
          //Clear render texture to clear color
          BeginTextureMode(target);
          ClearBackground(colors[0]);
          EndTextureMode();
        }

        if( IsMouseButtonDown(MOUSE_LEFT_BUTTON) || (GetGestureDetected() == GESTURE_DRAG) )
        {
          //Paint circle into render texture 
          //NOTE: To avoid discontinuous circles, we could store
          //previous-next mouse points and just draw a line using brushSize
          BeginTextureMode(target);
          if( mousePos.y > 50 ) DrawCircle((int)mousePos.x, (int)mousePos.y, (float)brushSize, colors[colorSelected]);
          EndTextureMode();
        }

        if( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) )
        {
          colorSelected = 0;

          //Erase circle from render texture 
          BeginTextureMode(target);
          if( mousePos.y > 50 ) DrawCircle((int)mousePos.x, (int)mousePos.y, (float)brushSize, colors[0]);
          EndTextureMode();
        }
        else colorSelected = colorSelectedPrev;

        //Check mouse hover save button 
        if( CheckCollisionPointRec(mousePos, btnSaveRec) ) btnSaveMouseHover = true;
        else btnSaveMouseHover = false;

        //Image saving logic
        //NOTE: Saving painted texture to a default named image
        if( (btnSaveMouseHover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_S) )
        {
          Image image = GetTextureData(target.texture);
          ImageFlipVertical(&image);
          ExportImage(image, "my_amazing_texture_painting.png");
          UnloadImage(image);
          showSaveMessage = true;
        }

        if( showSaveMessage )
        {
          //On saving, show a full screen message for 2 seconds
          saveMessageCounter++;
          if( saveMessageCounter > 240 )
          {
            showSaveMessage = false;
            saveMessageCounter = 0;
          }
        }
        
        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          //NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
          DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);

          //Draw drawing circle for reference
          if( mousePos.y > 50 )
          {
            if( IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ) DrawCircleLines((int)mousePos.x, (int)mousePos.y, (float)brushSize, GRAY);
            else DrawCircle( GetMouseX(), GetMouseY(), (float)brushSize, colors[colorSelected]);
          }

          //Draw top panel
          DrawRectangle(0, 0, screenWidth, 50, RAYWHITE);
          DrawLine(0,50,screenWidth, 50, LIGHTGRAY);

          //Draw color selection rectangles
          for( int i = 0; i < MAX_COLORS_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);
          DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

          if( colorMouseHover >= 0 ) DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));

          DrawRectangleLinesEx( (Rectangle){ colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
              colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4}, 2, BLACK);

          //Draw save image button 
          DrawRectangleLinesEx(btnSaveRec, 2, btnSaveMouseHover ? RED : BLACK);
          DrawText("SAVE!", 755, 20, 10, btnSaveMouseHover ? RED : BLACK);

          //Draw save image message
          if( showSaveMessage )
          {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.8f));
            DrawRectangle(0, 150, screenWidth, 80, BLACK);
            DrawText("IMAGE SAVED: my_amazing_texture_painting.png", 150, 180, 20, RAYWHITE);
          }

        EndDrawing();
    }

    //Clean memory
    UnloadRenderTexture(target);

    //Clear
    CloseWindow();

    return 0;
}

