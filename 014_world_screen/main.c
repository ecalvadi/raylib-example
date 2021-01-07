/**
 *
 * This example show how works a 3D camera and 
 * text over 3D cube object  
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D World Screen");

    //Define the camera to look into our 3D world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; //Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      //Camera looking at point 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          //Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                //Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                   //Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector2 cubeScreenPosition = { 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE);                 //Set a free camera mode 


    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        UpdateCamera(&camera);

        //Calculate cube screen space position (with a little offset to be in top)
        cubeScreenPosition = GetWorldToScreen( (Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera );


        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode3D(camera);

            DrawCube( cubePosition, 2.0f, 2.0f, 2.0f, RED );
            DrawCubeWires( cubePosition, 2.0f, 2.0f, 2.0f, MAROON );

            DrawGrid(10, 1.0f);
            
          EndMode3D();

          DrawText("Enemy: 100 / 100", cubeScreenPosition.x - MeasureText("Enemy: 100 / 100", 20) / 2, cubeScreenPosition.y, 20, BLACK );
          DrawText("Text is always on top of the cube", (screenWidth - MeasureText("Text is always on top of the cube", 20)) / 2, 25, 20, GRAY);

          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}
