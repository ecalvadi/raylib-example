/**
 *This example show images loading in RAM and textures loaded in GPU
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image loading and Drawing on it");

    //Loading textures and images
    Image cat = LoadImage("resources/cat.png");                               //Load image in CPU memory (RAM)
    ImageCrop(&cat, (Rectangle){ 100, 100, 280, 380});      //Crop an image piece
    ImageFlipHorizontal(&cat);                                                        //Flip cropped image horizontally
    ImageResize(&cat, 150, 200);                                  //Resize flipped-cropped iamge

    Image parrots = LoadImage("resources/parrots.png");                      //Load image in CPU memory (RAM)

    //Draw one image over the other with a scaling of 1.5f
    ImageDraw(&parrots, cat, (Rectangle){ 0, 0, (float)cat.width, (float)cat.height}, (Rectangle){ 20, 40, (float)cat.width * 1.5f, (float)cat.height * 1.5f}, WHITE);
    ImageCrop(&parrots, (Rectangle){ 0, 50, (float)parrots.width, (float)parrots.height - 100}); //Crop resulting image

    //Fraw on the image with a few image draw methods
    ImageDrawPixel(&parrots, 10, 10, RAYWHITE);
    ImageDrawCircle(&parrots, 10, 10, 5, RAYWHITE);
    ImageDrawRectangle(&parrots, 5, 20, 10, 10, RAYWHITE);

    UnloadImage(cat);       //Unload image from RAM

    //Load custom font for drawing on image
    Font font = LoadFont("resources/custom_jupiter_crash.png");

    //Draw over image using custom font
    ImageDrawTextEx(&parrots, font, "PARROTS & CAT", (Vector2){ 300, 230 }, (float)font.baseSize, -2, WHITE);

    UnloadFont(font);       //Unload custom spritefont (already drawn used on image)

    Texture2D texture = LoadTextureFromImage(parrots);        //Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(parrots);   //Once image has been converted to texture and uploaded to VRAM it can be unloaded from RAM


    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2 - 40, WHITE);
            DrawRectangleLines(screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2 - 40, texture.width, texture.height, DARKGRAY );

            DrawText("We are drawing only one texture from various images composed!", 500, 650, 10, DARKGRAY);
            DrawText("Source images have been cropped, scaled, flipped and copied one over the other.", 440, 670, 10, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);
    //Clear
    CloseWindow();

    return 0;
}

