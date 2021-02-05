/**
 *This example load an image and set as texture
 *
 * */

#include <raylib.h>

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image loading");

    //Textures mus be loaded after window initialization (OpenGL is needed)
    Image image = LoadImage("resources/raylib_logo.png");   //Load image in RAM by CPU
    Texture2D texture = LoadTextureFromImage(image);                //Convert image to texture, pass to GPU memory (VRAM)

    UnloadImage(image);     //Clean image RAM usage that is not needed

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, (screenWidth / 2) - (texture.width / 2), (screenHeight / 2) - (texture.height / 2), WHITE);

            DrawText("this Is a texture loaded from an image!", 300, 370, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);  //Clean GPU memory

    //Clear
    CloseWindow();

    return 0;
}

