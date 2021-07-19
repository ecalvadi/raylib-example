/**
 * This example shows a button based on sprites in the middle of the screen
 * 
 * */

#include <raylib.h>

#define NUM_FRAMES 3        // Number of frames (rectangles) for the button sprite texture

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Sprite Button");

    InitAudioDevice();      //Initialize audio device

    Sound fxButton = LoadSound("resources/buttonfx.wav");       // Load button sound
    Texture2D button = LoadTexture("resources/button.png");     // Load button texture

    //Define frame rectangle for drawing
    float frameHeight = (float)button.height/NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight};

    //Define button bounds on screen
    Rectangle buttonBounds = {screenWidth/2.0f - button.width/2.0f,
                              screenHeight/2.0f -  button.height/NUM_FRAMES/2.0f,
                              (float)button.width, frameHeight};

    int btnState = 0;           // Button State: 0-NORMAL, 1-MOUSE OVER, 2-PRESSED
    bool btnAction = false;     // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f};

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        mousePoint = GetMousePosition();
        btnAction = false;

        // check button state
        if (CheckCollisionPointRec(mousePoint, buttonBounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) btnAction = true;
        }
        else btnState = 0;

        if (btnAction)
        {
            PlaySound(fxButton);

            //TODO: Any desire action
        }


        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = btnState*frameHeight;

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextureRec(button, sourceRec, (Vector2){ buttonBounds.x, buttonBounds.y }, WHITE); // Draw button Frame

            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(button);  // Unload Button texture
    UnloadSound(fxButton);  // Unload Sound

    CloseAudioDevice();     // Close audio device

    //Clear
    CloseWindow();

    return 0;
}

