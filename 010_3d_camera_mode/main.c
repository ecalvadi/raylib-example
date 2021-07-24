/**
 *
 * This example show how works a 2D camera 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D Camera Mode");

    //Define the camera to loo into our 3d World
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  //Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      //Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          //Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                           //Camera field of view Y
    camera.projection = CAMERA_PERSPECTIVE;                              //Camera mode type

    //Set cube position
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(0, 0);

            //DrawRectangle(0, 640, 1280, 720, GRAY);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}