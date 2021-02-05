/**
 *This example load an image and set as texture then proccess the image with diferent
 *
 * */

#include <raylib.h>

#include <stdlib.h> //Required for: free()

#define NUM_PROCESSES   8

typedef enum {
    NONE = 0,
    COLOR_GRAYSCALE,
    COLOR_TINT,
    COLOR_INVERT,
    COLOR_CONTRAST,
    COLOR_BRIGHTNESS,
    FLIP_VERTICAL,
    FLIP_HORIZONTAL
} ImageProcess;

static const char *processText[] = {
        "NO PROCESSING",
        "COLOR GRAYSCALE",
        "COLOR TINT",
        "COLOR INVERT",
        "COLOR CONTRAST",
        "COLOR BRIGHTNESS",
        "FLIP VERTICAL",
        "FLIP HORIZONTAL"
};

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Image processing");

    //Textures mus be loaded after window initialization (OpenGL is needed)
    Image image = LoadImage("resources/parrots.png");   //Load image to RAM
    ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);       //Format image to RGBA 32bit (required for texture update) <-- ISSUE
    Texture2D texture = LoadTextureFromImage(image);             // Image converted to texture and load to VRAM

    int currentProcess = NONE;
    bool textureReload = false;

    Rectangle toggleRecs[NUM_PROCESSES] = { 0 };
    int mouseHoverRec = -1;

    for(int i = 0; i < NUM_PROCESSES; i++) toggleRecs[i] = (Rectangle){40.0f, (float)(50 + 32 * i), 150.0f, 30.0f};

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update

        //Mouse toggle group loginc
        for( int i = 0; i < NUM_PROCESSES; i++ )
        {
            if( CheckCollisionPointRec(GetMousePosition(), toggleRecs[i]) )
            {
                mouseHoverRec = i;

                if( IsMouseButtonReleased(MOUSE_LEFT_BUTTON) )
                {
                    currentProcess = i;
                    textureReload = true;
                }
                break;
            }
            else mouseHoverRec = -1;
        }

        //Keyboar toggle group logic
        if( IsKeyPressed(KEY_DOWN) )
        {
            currentProcess++;
            if( currentProcess > 7 ) currentProcess = 0;
            textureReload = true;
        }
        else if( IsKeyPressed(KEY_UP) )
        {
            currentProcess--;
            if( currentProcess  < 0) currentProcess = 7;
            textureReload = true;
        }

        //Reload texture when required
        if( textureReload )
        {
            UnloadImage(image);                             //Unload current image data
            image = LoadImage("resources/parrots.png");     //Re-load image data

            // NOTE: Image processing is costly CPU process to be done every frame,
            // If image processing is required in a frame-basis, it should be done
            // with a texture and by shaders
            switch (currentProcess) {
                case COLOR_GRAYSCALE: ImageColorGrayscale(&image); break;
                case COLOR_TINT: ImageColorTint(&image, GREEN); break;
                case COLOR_INVERT: ImageColorInvert(&image); break;
                case COLOR_CONTRAST: ImageColorContrast(&image, -40); break;
                case COLOR_BRIGHTNESS: ImageColorBrightness(&image, -80); break;
                case FLIP_VERTICAL: ImageFlipVertical(&image); break;
                case FLIP_HORIZONTAL: ImageFlipHorizontal(&image);
                default: break;
            }

            Color *pixels = GetImageData(image);        // Get pixel data from image (RGBA 32bit)
            UpdateTexture(texture, pixels);             // Update texture with new image data
            free(pixels);                               // Unload pixels data from RAM

            textureReload = false;
        }

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("IMAGE PROCESSING", 40, 30, 10, DARKGRAY);

            //Draw rectangles
            for( int i = 0; i < NUM_PROCESSES; i++ )
            {
                DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY);
                DrawRectangleLines( (int)toggleRecs[i].x, (int)toggleRecs[i].y, (int)toggleRecs[i].width,
                                    (int)toggleRecs[i].height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY );
                DrawText( processText[i],
                          (int)( toggleRecs[i].x + (toggleRecs[i].width / 2) - MeasureText(processText[i], 10) / 2),
                          (int)toggleRecs[i].y + 11, 10, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY );

            }

            DrawTexture(texture, (screenWidth - texture.width - 60), (screenHeight / 2) - (texture.height / 2), WHITE);
            DrawRectangleLines( (screenWidth - texture.width - 60), (screenHeight / 2) - (texture.height / 2), texture.width, texture.height, BLACK );

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texture);
    UnloadImage(image);

    //Clear
    CloseWindow();

    return 0;
}

