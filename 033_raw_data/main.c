/**
 *This example load Textures from raw data 
 *
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

#include <stdlib.h>       // Required for: malloc() and free()

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image loading from RAW DATA");

    // Load RAW image data (512x512, 32bit RGBA, no file header)
    Image fudesumiRaw = LoadImageRaw("resources/fudesumi.raw", 384, 512, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 0);
    Texture2D fudesumi = LoadTextureFromImage(fudesumiRaw);    // Upload CPU (RAM) image to GPU (VRAM)
    UnloadImage(fudesumiRaw);                                  // Unload CPU (RAM) image data 

    // Generate a checked texture by code 
    int width = 1310;
    int height = 750;

    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width * height * sizeof(Color));

    for( int y = 0; y < height; y++ )
    {
      for( int x = 0; x < width; x++ )
      {
        if( ((x/32 + y/32)) % 2 == 0) pixels[y*width + x] = ORANGE;
        else pixels[y*width + x] = GOLD;
      }
    }

    // Load pixels data into an image structure and create texture 
    Image checkedIm = {
      .data = pixels,
      .width = width,
      .height = height,
      .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
      .mipmaps = 1
    };

    Texture2D checked = LoadTextureFromImage(checkedIm);
    UnloadImage(checkedIm);        // Unload CPU (RAM) image data (pixels)

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(checked, screenWidth/2 - checked.width/2, screenHeight/2 - checked.height/2, Fade(WHITE, 0.5f));
            DrawTexture(fudesumi, 730, 100, WHITE);

            DrawText("CHECKED TEXTURE", 84, 85, 30, BROWN);
            DrawText("GENERATED by CODE", 72, 148, 30, BROWN);
            DrawText("and RAW IMAGE LOADING", 46, 210, 30, BROWN);

            DrawText("(c) Fudesumi sprite by Eiden Marsal", 510, screenHeight - 20, 10, BROWN);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(fudesumi);  //Clean GPU memory
    UnloadTexture(checked);

    //Clear
    CloseWindow();

    return 0;
}

