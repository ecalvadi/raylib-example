/**
 *This example npatch textures, for GUI
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - N-Patch Drawing");

    // NOTE: Textures MUST be loaded after Window Initialization (OpenGL context is required)
    Texture2D nPatchTexture = LoadTexture("resources/ninepatch_button.png");

    Vector2 mousePosition;// = { 0 };
    Vector2 origin = { 0.0f, 0.0f };

    // Position and size of the n-patches
    Rectangle dstRect1 = { 400.0f, 160.0f, 32.0f, 32.0f};
    Rectangle dstRect2 = { 160.0f, 160.0f, 32.0f, 32.0f};
    Rectangle dstRectH = { 160.0f, 93.0f, 32.0f, 32.0f};
    Rectangle dstRectV = { 92.0f, 160.0f, 32.0f, 32.0f};

    // A 9-patch (NPT_9PATCH changes its sizes in both axis
    NPatchInfo  ninePatchInfo1 = { (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f }, 12,40, 12, 12, NPATCH_NINE_PATCH};
    NPatchInfo  ninePatchInfo2 = { (Rectangle){ 0.0f, 128.0f, 64.0f, 64.0f }, 16,16, 16, 16, NPATCH_NINE_PATCH};

    // A horizontal 3-patch (NPT_3PATCH_HORIZONTAL) changes its sizes along the x axis only
    NPatchInfo h3PatchInfo = { (Rectangle){ 0.0f, 64.0f, 64.0f, 64.0f}, 8, 8, 8, 8, NPATCH_THREE_PATCH_HORIZONTAL};

    // A vertical 3-patch (NPT_3PATCH_VERTICAL) changes its sizes along the y axis only
    NPatchInfo v3PatchInfo = { (Rectangle){ 0.0f, 192.0f, 64.0f, 64.0f}, 6, 6, 6, 6, NPATCH_THREE_PATCH_VERTICAL};


    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        mousePosition = GetMousePosition();

        // Resize the n-patches based on mouse position
        dstRect1.width = mousePosition.x - dstRect1.x;
        dstRect1.height = mousePosition.y - dstRect1.y;
        dstRect2.width = mousePosition.x - dstRect2.x;
        dstRect2.height = mousePosition.y - dstRect2.y;
        dstRectH.width = mousePosition.x - dstRectH.x;
        dstRectV.height = mousePosition.y - dstRectV.y;

        // Set a minimun width and/or height 
        if(dstRect1.width < 1.0f ) dstRect1.width = 1.0f;
        if(dstRect1.width > 300.0f ) dstRect1.width = 300.0f;
        if(dstRect1.height < 1.0f ) dstRect1.height = 1.0f;
        if(dstRect2.width < 1.0f ) dstRect2.width = 1.0f;
        if(dstRect2.width > 300.0f ) dstRect2.width = 300.0f;
        if(dstRect2.height < 1.0f ) dstRect2.height = 1.0f;
        if(dstRectH.width < 1.0f ) dstRectH.width = 1.0f;
        if(dstRectV.height < 1.0f ) dstRectV.height = 1.0f;

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw the n-patches 
            DrawTextureNPatch(nPatchTexture, ninePatchInfo2, dstRect2, origin, 0.0f, WHITE);
            DrawTextureNPatch(nPatchTexture, ninePatchInfo1, dstRect1, origin, 0.0f, WHITE);
            DrawTextureNPatch(nPatchTexture, h3PatchInfo, dstRectH, origin, 0.0f, WHITE);
            DrawTextureNPatch(nPatchTexture, v3PatchInfo, dstRectV, origin, 0.0f, WHITE);

            // Draw the source Texture 
            DrawRectangleLines( 5, 88, 74, 266, BLUE);
            DrawTexture(nPatchTexture, 10, 93, WHITE);
            DrawText("TEXTURE", 15, 360, 10, DARKGRAY);

            DrawText("move the mouse to stretch or shrink the n-patches", 10, 30, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(nPatchTexture);

    //Clear
    CloseWindow();

    return 0;
}

