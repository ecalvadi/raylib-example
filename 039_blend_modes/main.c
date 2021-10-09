/**
 * This example show a blend modes showing alpha textures, etc 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Blend Modes");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Image bgImage = LoadImage("resources/cyberpunk_street_background.png"); // Load in CPU Memory (RAM)
    Texture2D bgTexture = LoadTextureFromImage(bgImage); // Image converted to Texture, GPU memory (VRAM)

    Image fgImage = LoadImage("resources/cyberpunk_street_foreground.png"); // Load in CPU Memory (RAM)
    Texture fgTexture = LoadTextureFromImage(fgImage); // Image converted to Texture, GPU Memory (VRAM)
    
    // Once image has converted to Texture and upload to VRAM, it can be unloaded from RAM
    UnloadImage(bgImage);
    UnloadImage(fgImage);

    const int blendCountMax = 4;
    BlendMode blendMode = 0;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        if (IsKeyPressed(KEY_SPACE))
        {
            if (blendMode >= (blendCountMax-1)) blendMode = 0;
            else ++blendMode;
        }
        
        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(bgTexture, screenWidth/2 - bgTexture.width/2, screenHeight/2 - bgTexture.height/2, WHITE);

            // Apply the blend mode and then draw the foreground texture
            BeginBlendMode(blendMode);
                DrawTexture(fgTexture, screenWidth/2 - fgTexture.width/2, screenHeight/2 - fgTexture.height/2, WHITE);
            EndBlendMode();

            // Draw the texts
            DrawText("Press SPACE to change blend modes.", 440, 550, 20, GRAY);

            switch (blendMode)
            {
                case BLEND_ALPHA: DrawText("Current: BLEND_ALPHA", (screenWidth / 2) - 160, 170, 20, GRAY); break;
                case BLEND_ADDITIVE: DrawText("Current: BLEND_ADDITIVE", (screenWidth / 2) - 160, 170, 20, GRAY); break;
                case BLEND_MULTIPLIED: DrawText("Current: BLEND_MULTIPLIED", (screenWidth / 2) - 160, 170, 20, GRAY); break;
                case BLEND_ADD_COLORS: DrawText("Current: BLEND_ADD_COLORS", (screenWidth / 2) - 160, 170, 20, GRAY); break;
                default: break;
            }

            DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clear
    UnloadTexture(fgTexture); // Unload foreground texture
    UnloadTexture(bgTexture); // Unload background texture

    CloseWindow();

    return 0;
}

