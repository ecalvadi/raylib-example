/**
 *
 * This example show how works a 3D camera and 
 * select an 3D object 
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
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D Camera Picking Object");

    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; //Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      //Camera looking at point 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          //Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                //Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   //Camera mode type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    Ray ray = { 0 };                                    //Picking line ray

    bool collision = false;

    SetCameraMode(camera, CAMERA_FREE);                 //Set a free camera mode 


    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        UpdateCamera(&camera);

        if( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
        {
          if( !collision )
          {
            ray = GetMouseRay( GetMousePosition(), camera );

            //Check the collision between ray and box
            collision = CheckCollisionRayBox( ray,
                (BoundingBox)
                { 
                  (Vector3)
                  { 
                    cubePosition.x - cubeSize.x / 2,
                    cubePosition.y - cubeSize.y / 2,
                    cubePosition.z - cubeSize.z / 2
                  },
                  (Vector3)
                  {
                    cubePosition.x + cubeSize.x / 2,
                    cubePosition.y + cubeSize.y / 2,
                    cubePosition.z + cubeSize.z / 2
                  }
                }
            );
          }
          else collision = false;
        }

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode3D(camera);
            
            if( collision )
            {
              DrawCube( cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED );
              DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON );

              DrawCubeWires(cubePosition, cubeSize.x + 0.02f, cubeSize.y + 0.2f, cubeSize.z + 0.02f, GREEN );
            }
            else 
            {
              DrawCube( cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY );
              DrawCubeWires( cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY );
            }

            DrawRay( ray, MAROON );
            DrawGrid(10, 1.0f);

          EndMode3D();

          DrawText("Try selecting the box with the mouse!", 440, 10, 20, DARKGRAY);

          if( collision ) DrawText("BOX SELECTED", (screenWidth - MeasureText("BOX SELECTED", 30)) / 2,
                                   (int)((float)screenHeight * 0.1f), 30, GRAY);

          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}
