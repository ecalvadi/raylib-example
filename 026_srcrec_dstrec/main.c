/**
 *This example show a texture texture loading and drawing a part defined by a rectangle
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Texture source and Destination rectangles");

    //NOTE: Textures MUST be loaded after Window initialization (OpenGL contex is required
    Texture2D scarfy = LoadTexture("resources/scarfy.png");     //Texture loading

    int frameWidth = scarfy.width / 6;
    int frameHeight = scarfy.height;

    //Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    //Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { (float)screenWidth / 2, (float)screenHeight / 2, (float)frameWidth * 2, (float)frameHeight * 2 };

    //Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { (float)frameWidth, (float)frameHeight };

    int rotation = 0;

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        rotation++;

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);


            DrawLine( (int)destRec.x, 0, (int)destRec.x, screenHeight, GRAY);
            DrawLine(0, (int)destRec.y, screenWidth, (int)destRec.y, GRAY);
            DrawTexturePro(scarfy, sourceRec, destRec, origin, (float)rotation, WHITE);

            DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(scarfy);

    //Clear
    CloseWindow();

    return 0;
}

