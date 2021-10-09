/**
 *This example load an image and drawing text using TTF 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image Text TTF");

    Image parrots = LoadImage("resources/parrots.png");

    //TTF Font loading with custom generation paramethers
    Font font = LoadFontEx("resources/KAISG.ttf", 64, 0, 0);

    //Draw over image using custom font
    ImageDrawTextEx(&parrots, font, "[Parrots font drawing]", (Vector2){ 20.0f, 20.0f }, (float)font.baseSize, 0.0f, RED);

    Texture2D texture = LoadTextureFromImage(parrots); // Image converted to texture, uploaded to VRAM
    UnloadImage(parrots); // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    Vector2 position = { ((float)screenWidth / 2 - (float)texture.width / 2), ((float)screenHeight / 2 - (float)texture.height / 2 - 20) };

    bool showFont = false;

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        if( IsKeyDown(KEY_SPACE) ) showFont = true;
        else showFont = false;

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if( !showFont )
            {
              //Draw texture with text already drawn inside
              DrawTextureV(texture, position, WHITE);

              //Draw text directly using sprite font 
              DrawTextEx(font, "[Parrots font drawing]", (Vector2){ position.x + 20, position.y + 20 + 280 }, (float)font.baseSize, 0.0f, WHITE);

            }
            else DrawTexture(font.texture, screenWidth / 2 - font.texture.width / 2, 50, BLACK);

            DrawText("PRESS SPACE to SEE USED SPRITEFONT", 490, 620, 10, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);

    //Clear
    CloseWindow();

    return 0;
}

