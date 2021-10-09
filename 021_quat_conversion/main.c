/**
 *Generally you should really stick to eluers OR quats...
 *This tests that various conversion are equivalent
 *
 * */

#ifdef OSX
  #include "../lib/raylib.h"
  #include "../lib/raymath.h"
#else
  #include <raylib.h>
  #include <raymath.h>
#endif

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Quat Conversion");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  //Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      //Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          //Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                //Camera field of view Y
    camera.projection = CAMERA_PERSPECTIVE;                   //Camera mode type

    Mesh mesh = GenMeshCylinder( 0.2f, 1.0f, 32);
    Model model = LoadModelFromMesh(mesh);

    //Some required variables
    Quaternion q1;// = { 0 };
    Matrix m1, m2 , m3, m4;
    Vector3 v1 = { 0 }, v2;

    //One PIx2 calc 

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop 
        if( !IsKeyDown(KEY_SPACE) )
        {
          v1.x += 0.01f;
          v1.y += 0.03f; 
          v1.z += 0.05f;
        }

        if( v1.x > PI * 2) v1.x -= PI * 2;
        if( v1.y > PI * 2) v1.y -= PI * 2;
        if( v1.y > PI * 2) v1.y -= PI * 2;

        q1 = QuaternionFromEuler(v1.x, v1.y, v1.z);
        m1 = MatrixRotateZYX(v1);
        m2 = QuaternionToMatrix(q1);

        q1 = QuaternionFromMatrix(m1);
        m3 = QuaternionToMatrix(q1);

        v2 = QuaternionToEuler(q1);
        v2.x *= DEG2RAD;
        v2.y *= DEG2RAD;
        v2.z *= DEG2RAD;

        m4 = MatrixRotateZYX(v2);

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode3D(camera);

            model.transform = m1;
            DrawModel(model, (Vector3){ -1, 0, 0 }, 1.0f, RED);

            model.transform = m2;
            DrawModel(model, (Vector3){ 1, 0, 0 }, 1.0f, RED);

            model.transform = m3;
            DrawModel(model, (Vector3){ 0, 0, 0 }, 1.0f, RED);

            model.transform = m4;
            DrawModel(model, (Vector3){ 0, 0, -1 }, 1.0f, RED);

            DrawGrid(10, 1.0f);

          EndMode3D();

          if( v2.x < 0) v2.x += PI * 2;
          if( v2.y < 0) v2.y += PI * 2;
          if( v2.z < 0) v2.z += PI * 2;

          Color cx, cy, cz;
          cx = cy = cz = BLACK;
          if( v1.x == v2.x ) cx = GREEN;
          if( v1.y == v2.y ) cy = GREEN;
          if( v1.z == v2.z ) cz = GREEN;

          DrawText( TextFormat("%2.3f", v1.x), 20, 40, 20, cx);
          DrawText( TextFormat("%2.3f", v1.y), 20, 60, 20, cy);
          DrawText( TextFormat("%2.3f", v1.z), 20, 80, 20, cz);

          DrawText( TextFormat("%2.3f", v2.x), 200, 40, 20, cx);
          DrawText( TextFormat("%2.3f", v2.y), 200, 60, 20, cy);
          DrawText( TextFormat("%2.3f", v2.z), 200, 80, 20, cz);

          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadModel(model);

    //Clear
    CloseWindow();

    return 0;
}

