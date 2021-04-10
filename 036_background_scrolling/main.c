/**
 * This example shows a background scrolling with a parallax effect
 * 
 * */

#include <raylib.h>

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Background Scrolling");

    // NOTE: Be careful, backfround width must be equal or bigger than screen width
    // if mot, texture should be draw more than two times for scrolling effect 
    Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Texture2D midground = LoadTexture("resources/cyberpunk_street_midground.png");
    Texture2D foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

    float scrollBack = 0.0f;
    float scrollMid = 0.0f;
    float scrollFore = 0.0f;

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        scrollBack -= 0.1f;
        scrollMid -= 0.5f;
        scrollFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it should be considered on scrolling 
        if (scrollBack <= -background.width * 2) scrollBack = 0;
        if (scrollMid <= -midground.width * 2) scrollMid = 0;
        if (scrollFore <= -foreground.width * 2) scrollFore = 0;

        //StartDrawing
        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            // Draw background image twice 
            // Note: Texture is scaled twice its size 
            DrawTextureEx(background, (Vector2){ scrollBack, 220 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width * 2 + scrollBack, 220 }, 0.0f, 2.0f, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, (Vector2){ scrollMid, 260}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width * 2 + scrollMid, 260}, 0.0f, 2.0f, WHITE);

            // Draw foreground image twice 
            DrawTextureEx(foreground, (Vector2){ scrollFore, 340}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){foreground.width * 2 + scrollFore, 340}, 0.0f, 2.0f, WHITE);

            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);


    //Clear
    CloseWindow();

    return 0;
}

