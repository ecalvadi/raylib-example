/**
 *
 * This example show how works a 3D camera with movement
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D Camera FREE");

    //Define cthe camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };     //Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f};           //Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              //Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                                //Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                                   //camera mode type

    //Set cube position
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f};

    SetCameraMode(camera, CAMERA_FREE);                         //Set a free camera mode

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        UpdateCamera(&camera);      //Update camera

        if( IsKeyDown(KEY_Z) ) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f};

        //StartDrawing
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);

                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawRectangle( 10, 30, 320, 133, Fade(SKYBLUE, 0.5f) );
            DrawRectangleLines( 10, 30, 320, 133, BLUE);

            DrawText("Free camera default controls:", 20, 40, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to pan", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 100, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 120, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 140, 10, DARKGRAY);

            DrawFPS(10, 10);
        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}