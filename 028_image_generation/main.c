/**
 *This example we generate an image from procedural algorithms
 *
 * */

#include <raylib.h>

#define NUM_TEXTURES 7  //Currently we have 7 generation Algorithms

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Procedural images generation");

    Image verticalGradient = GenImageGradientV(screenWidth, screenHeight, RED, BLUE);
    Image horizontalGradient = GenImageGradientH(screenWidth, screenHeight, RED,BLUE);
    Image radialGradient = GenImageGradientRadial(screenWidth, screenHeight, 0.0f, WHITE, BLACK);
    Image checked = GenImageChecked(screenWidth, screenHeight, 32, 32, RED, BLUE);
    Image whiteNoise = GenImageWhiteNoise(screenWidth, screenHeight, 0.5f);
    Image perlinNoise = GenImagePerlinNoise(screenWidth, screenHeight, 50, 50, 4.0f);
    Image cellular = GenImageCellular(screenWidth, screenHeight, 32);

    Texture2D textures[NUM_TEXTURES] = { 0 };

    textures[0] = LoadTextureFromImage(verticalGradient);
    textures[1] = LoadTextureFromImage(horizontalGradient);
    textures[2] = LoadTextureFromImage(radialGradient);
    textures[3] = LoadTextureFromImage(checked);
    textures[4] = LoadTextureFromImage(whiteNoise);
    textures[5] = LoadTextureFromImage(perlinNoise);
    textures[6] = LoadTextureFromImage(cellular);

    //Unload image data (CPU RAN)
    UnloadImage(verticalGradient);
    UnloadImage(horizontalGradient);
    UnloadImage(radialGradient);
    UnloadImage(checked);
    UnloadImage(whiteNoise);
    UnloadImage(perlinNoise);
    UnloadImage(cellular);

    int currentTexture = 0;

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_RIGHT))
        {
            currentTexture = (currentTexture + 1) % NUM_TEXTURES; //Cycle between the textures
        }

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(textures[currentTexture], 0, 0, WHITE);

            DrawRectangle(30, 580, 325, 30, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(30, 580, 325, 30, Fade(WHITE, 0.5f));
            DrawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL TEXTURES", 40, 590, 10, WHITE);

            switch (currentTexture) {
                case 0: DrawText("VERTICAL GRADIENT", 560, 10, 20, RAYWHITE); break;
                case 1: DrawText("HORIZONTAL GRADIENT", 540, 10, 20, RAYWHITE); break;
                case 2: DrawText("RADIAL GRADIENT", 580, 10, 20, RAYWHITE); break;
                case 3: DrawText("CHECKED", 680, 10, 20, RAYWHITE); break;
                case 4: DrawText("WHITE NOISE", 640, 10, 20, RAYWHITE); break;
                case 5: DrawText("PERLIN NOISE", 630, 10, 20, RAYWHITE); break;
                case 6: DrawText("CELLULAR", 670, 10, 20, RAYWHITE); break;
                default: break;
            }

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    for(int i = 0; i < NUM_TEXTURES; i++) UnloadTexture(textures[i]);

    //Clear
    CloseWindow();

    return 0;
}

