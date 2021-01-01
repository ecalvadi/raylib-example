/**
 *
 * This example show how works a 3D camera with movement
 *
 * */

#include <raylib.h>

#define MAX_COLUMNS 20

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D Camera First Person");

    //Define cthe camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };     //Camera position
    camera.target = (Vector3){ 0.0f, 10.8f, 0.0f};           //Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              //Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                                //Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                                   //camera mode type

    //Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    Vector3 position[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for( int i = 0; i < MAX_COLUMNS; i++ )
    {
        heights[i] = (float)GetRandomValue(1, 12);
        position[i] = (Vector3){ GetRandomValue(-15, 15), heights[i] / 2, GetRandomValue(-15, 15) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }

    //Set camera first_person
    SetCameraMode(camera, CAMERA_FIRST_PERSON);                         //Set a free camera mode

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        UpdateCamera(&camera);      //Update camera

        //StartDrawing
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawPlane( (Vector3){0.0f, 0.0f, 0.0f}, (Vector2){ 64.0f, 64.0f }, LIGHTGRAY ); //Draw ground
                DrawCube( (Vector3){ -32.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 64.0f, BLUE );   //Draw a blue wall
                DrawCube( (Vector3){ 32.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 64.0f, LIME );    //Draw a green wall
                DrawCube( (Vector3){ 0.0f, 2.5f, -32.0f }, 64.0f, 5.0f, 1.0f, GOLD );   //Draw a yellow wall
                DrawCube( (Vector3){ 0.0f, 2.5f, 32.0f }, 64.0f, 5.0f, 1.0f, MAROON );  //Draw a Maroon wall

                //Draw some pillars around
                for( int i = 0; i < MAX_COLUMNS; i++ )
                {
                    DrawCube(position[i], 2.0f, heights[i], 2.0f, colors[i]);
                }

            EndMode3D();

            DrawRectangle(10, 30, 220, 70, Fade(SKYBLUE, 0.5f) );
            DrawRectangleLines(10, 30, 220, 70, BLUE);

            DrawText("First person camera default controls:", 20, 40, 10, BLACK);
            DrawText("- Move with keys: W, A, S, D", 40, 60, 10, DARKGRAY);
            DrawText("- Mouse move to look around", 40, 80, 10, DARKGRAY);

            DrawFPS(10, 10);
        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}