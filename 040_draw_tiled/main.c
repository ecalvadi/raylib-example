/**
 * This example Drawing part og the texture tiled
 * 
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

#define SIZEOF(A) (sizeof(A)/sizeof(A[0]))
#define OPT_WIDTH       220             // Max width for the options container
#define MARGIN_SIZE       8             // Size for the margins
#define COLOR_SIZE       16             // Size of the color select buttons

int main(void) {
    //Initialization of the screen resolution
    int screenWidth = 1280;
    int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  // Make the window resizable
    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Draw part of a texture tiled");

    // NOTE: Textures MUST be loaded after Window Initialization (OpenGL context is required)
    Texture texPattern = LoadTexture("resources/patterns.png");
    SetTextureFilter(texPattern, TEXTURE_FILTER_TRILINEAR); // Makes the texture smoother when upscaled

    // Coordinates for all patterns inside the texture
    const Rectangle recPattern[] = {
            (Rectangle){ 3, 3, 66, 66},
            (Rectangle){ 75, 3, 100, 100},
            (Rectangle){ 3, 75, 66, 66},
            (Rectangle){ 7, 156, 50, 50},
            (Rectangle){ 85, 106, 90, 45},
            (Rectangle){ 75, 154, 100, 60}
    };

    // Setup colors
    const Color colors[] = { BLACK, MAROON, ORANGE, BLUE, PURPLE, BEIGE, LIME, RED, DARKGRAY, SKYBLUE};
    enum { MAX_COLORS = SIZEOF(colors)};
    Rectangle colorRec[MAX_COLORS] = { 0 };

    // Calculate rectangle for each color
    for (int i = 0, x = 0, y=0; i < MAX_COLORS; i++)
    {
        colorRec[i].x = 2.0f + MARGIN_SIZE + x;
        colorRec[i].y = 22.0f + 256.0f + MARGIN_SIZE + y;
        colorRec[i].width = COLOR_SIZE*2.0f;
        colorRec[i].height = (float)COLOR_SIZE;

        if (i == (MAX_COLORS/2 - 1))
        {
            x = 0;
            y += COLOR_SIZE + MARGIN_SIZE;
        }
        else x += (COLOR_SIZE*2 + MARGIN_SIZE);
    }

    int activePattern = 0, activeCol = 0;
    float scale = 1.0f, rotation = 0.0f;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        //Handle Mouse
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            const Vector2 mouse = GetMousePosition();

            //Check witch pattern was clicked and set it as the active pattern
            for (int i=0; i < SIZEOF(recPattern); i++)
            {
                if (CheckCollisionPointRec(mouse, (Rectangle){ 2 + MARGIN_SIZE + recPattern[i].x, 40 + MARGIN_SIZE + recPattern[i].y, recPattern[i].width, recPattern[i].height}))
                {
                    activePattern = i;
                    break;
                }
            }

            // Check to see tich color was clicked and set it as the active color
            for (int i = 0; i < MAX_COLORS; i++)
            {
                if (CheckCollisionPointRec(mouse, colorRec[i]))
                {
                    activeCol = i;
                    break;
                }
            }
        }

        // Handle keys

        // Change scale
        if (IsKeyPressed(KEY_UP)) scale += 0.25f;
        if (IsKeyPressed(KEY_DOWN)) scale -= 0.25f;
        if (scale > 10.0f) scale = 10.0f;
        else if (scale <= 0.0f) scale = 0.25f;

        // Change rotation
        if (IsKeyPressed(KEY_LEFT)) rotation -= 25.0f;
        if (IsKeyPressed(KEY_RIGHT)) rotation += 25.0f;

        // Reset
        if (IsKeyDown((KEY_SPACE)))
        {
            rotation = 0.0f;
            scale = 1.0f;
        }

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw the tiled area
            DrawTextureTiled(
                    texPattern,
                    recPattern[activePattern],
                    (Rectangle){(float)OPT_WIDTH+MARGIN_SIZE, (float)MARGIN_SIZE, screenWidth - OPT_WIDTH - 2.0f*MARGIN_SIZE, screenHeight - 2.0f*MARGIN_SIZE},
                    (Vector2){0.0f, 0.0f}, rotation, scale, colors[activeCol]
            );

            // Draw options
            DrawRectangle(MARGIN_SIZE, MARGIN_SIZE, OPT_WIDTH - MARGIN_SIZE, screenHeight - 2*MARGIN_SIZE, ColorAlpha(LIGHTGRAY, 0.5f));

            DrawText("Select Pattern", 2 + MARGIN_SIZE, 30 + MARGIN_SIZE, 10, BLACK);
            DrawTexture(texPattern, 2 + MARGIN_SIZE, 40 + MARGIN_SIZE, BLACK);
            DrawRectangle(
                    2 + MARGIN_SIZE + (int)recPattern[activePattern].x,
                    40 + MARGIN_SIZE + (int)recPattern[activePattern].y,
                    (int)recPattern[activePattern].width,
                    (int)recPattern[activePattern].height,
                    ColorAlpha(DARKBLUE, 0.3f)
                    );

            DrawText("Select Color", 2+MARGIN_SIZE, 10+256+MARGIN_SIZE, 10, BLACK);
            for (int i = 0; i < MAX_COLORS; i++)
            {
                DrawRectangleRec(colorRec[i], colors[i]);
                if (activeCol == i) DrawRectangleLinesEx(colorRec[i], 3, ColorAlpha(WHITE, 0.5f));
            }

            DrawText("Scale (UP/DOWN to change)", 2 + MARGIN_SIZE, 80 + 256 + MARGIN_SIZE, 10, BLACK);
            DrawText(TextFormat("%.2fx", scale), 2 + MARGIN_SIZE, 92 + 256 + MARGIN_SIZE, 20, BLACK);

            DrawText("Rotation (LEFT/RIGHT to change)", 2 + MARGIN_SIZE, 122 + 256 + MARGIN_SIZE, 10, BLACK);
            DrawText(TextFormat("%.0f degrees", rotation), 2 + MARGIN_SIZE, 134 + 256 + MARGIN_SIZE, 20, BLACK);


            DrawText("Press [SPACE] to reset", 2 + MARGIN_SIZE, 164 + 256 + MARGIN_SIZE, 10, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clear
    UnloadTexture(texPattern);

    CloseWindow();

    return 0;
}

