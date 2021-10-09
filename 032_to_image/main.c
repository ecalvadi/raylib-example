/**
 *This example load an image and set as texture
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image loading from Texture");

    Image image = LoadImage("resources/raylib_logo.png");    // Load image data into CPU memory (RAM)
    Texture2D texture = LoadTextureFromImage(image);         // Image converted to texture, GPU memory (RAM -> VRAM)
    UnloadImage(image);                                      // Unload image data from CPU memory (RAM)

    image = GetTextureData(texture);                         // Retrieve image data from GPU memory (VRAM -> RAM)
    UnloadTexture(texture);                                  // Unload texture from GPU memory (VRAM)

    texture = LoadTextureFromImage(image);                   // Recreate texture from retrieved image data (RAM->VRAM)
    UnloadImage(image);                                      // Unload retrieved image data from CPU memory (RAM)

    //Set FPS 
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, (screenWidth / 2 - texture.width / 2), (screenHeight / 2 - texture.height / 2), WHITE);

            DrawText("this IS a texture loaded from a image!", 550, 640, 10, GRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);  //Clean GPU memory

    //Clear
    CloseWindow();

    return 0;
}

