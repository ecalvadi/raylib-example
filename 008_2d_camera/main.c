/**
 *
 * This example show how works a 2D camera 
 *
 * */

#include <raylib.h>

#define MAX_BUILDINGS 100

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    int speed = (fps == 60) ? 2 : 4;
    float zoomSpeed = (fps == 60) ? 0.05f : 0.1f;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 2D Camera");

    //Initialization of the player and buildings
    Rectangle player = { 400, 550, 40, 40 };
    Rectangle buildings[MAX_BUILDINGS] = { 0 };
    Color buildColors[MAX_BUILDINGS] = { 0 };

    //set spacing to 0 to place buildings close
    int spacing = 0;

    //Creating buildings 
    for( int i = 0; i < MAX_BUILDINGS; i++ )
    {
      //Set width and height randomly
      buildings[i].width = GetRandomValue(50, 200);
      buildings[i].height = GetRandomValue(100, 800);

      //Setting building position
      buildings[i].y = screenHeight - 130 - buildings[i].height;
      buildings[i].x = -6000 + spacing;

      spacing += buildings[i].width;

      //Set building color randomly
      buildColors[i] = (Color){ GetRandomValue(200, 240), GetRandomValue(200, 240), GetRandomValue(200, 250), 255 };
    }

    //Set the camera settings
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20, player.y + 20 }; //Camera around the target
    camera.offset = (Vector2){ screenWidth/2, screenHeight - 100 }; // camera offset (movement)
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        //player movement (keyboard and joystick)
        if( IsKeyDown(KEY_D) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ) player.x += speed;
        else if ( IsKeyDown(KEY_A) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ) player.x -= speed;

        // Camera target follows player 
        camera.target = (Vector2){ player.x + 20, player.y + 20 };

        //Camera rotation control 
        if( IsKeyDown(KEY_Q) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1) ) camera.rotation -= speed;
        else if( IsKeyDown(KEY_E) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) ) camera.rotation += speed;

        //Limit the camera rotation to 80 degrees (-40 to 40);
        if( camera.rotation > 40 ) camera.rotation = 40;
        else if( camera.rotation < -40) camera.rotation = -40;

        //Camera zoom controls
        camera.zoom += ((float)GetMouseWheelMove() * zoomSpeed);
        //TODO: add joystick zoom support
        if( camera.zoom > 3.0f ) camera.zoom = 3.0f;
        else if( camera.zoom < 0.1f ) camera.zoom = 0.1f;

        //reset camera (zoom and rotation)
        if( IsKeyPressed(KEY_R) )
        {
          camera.zoom = 1.0f;
          camera.rotation = 0.0f;
        }

        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode2D(camera);

            DrawRectangle(-6000, 560, 13000, 8000, DARKGRAY);

            //Draw buildings
            for( int i = 0; i < MAX_BUILDINGS; i++ ) DrawRectangleRec(buildings[i], buildColors[i]);

            //Draw player
            DrawRectangleRec(player, RED);

            //Draw centered lines
            DrawLine(camera.target.x, -screenHeight * 10, camera.target.x, screenHeight * 10, GREEN);
            DrawLine(-screenWidth * 10, camera.target.y, screenWidth * 10, camera.target.y, GREEN);

          EndMode2D();

          DrawText("SCREEN AREA", 640, 10, 20, RED);

          DrawRectangle(0, 0, screenWidth, 5, RED);
          DrawRectangle(0, 5, 5, screenHeight - 10, RED);
          DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, RED);
          DrawRectangle(0, screenHeight - 5, screenWidth, 5, RED);

          //Drawing a blue box
          DrawRectangle( 10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
          DrawRectangleLines( 10, 10, 250, 113, BLUE);

          DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
          DrawText("- A / D to move offset", 40, 40, 10, DARKGRAY);
          DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
          DrawText("- Q / E to rodate", 40, 80, 10, DARKGRAY);
          DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

