/**
 *
 * This example show a controller that receive inputs from
 * a compatible controller (Xbox controller and PS3 controller)
 *
 * */

#include <raylib.h>

//Gamepad name ID depends on drivers and OS
#if defined(PLATFORM_RPI)
  #define XBOX360_NAME_ID "Microsoft X-Box 360 pad"
  #define PS3_NAME_ID     "PLAYSTATION(R)3 Controller"
  #define SHANWAN_NAME_ID "SHANWAN PS3 GamePad"
#else
  #define XBOX360_NAME_ID "Xbox 360 Controller"
  #define PS3_NAME_ID     "PLAYSTATION(R)3 Controller"
  #define SHANWAN_NAME_ID "SHANWAN PS3 GamePad"
#endif

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - GamePad Input");

    //Loading textures to show the controller
    Texture2D texPs3Pad = LoadTexture("assets/ps3.png");
    Texture2D texXboxPad = LoadTexture("assets/xbox.png");

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop

        //if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ToggleFullscreen();

        //Start Drawing
        BeginDrawing();

        //Painting the background with a darkgray color
        ClearBackground(RAYWHITE);

        //If player1 gamepad is available
        if( IsGamepadAvailable(GAMEPAD_PLAYER1) )
        {
            //Print text (text, posX, posY, size, Color)
            DrawText( FormatText( "GP1: %s", GetGamepadName(GAMEPAD_PLAYER1) ), 10, 10, 10, BLACK);

            //If gamepad is XBOX
            if( IsGamepadName(GAMEPAD_PLAYER1, XBOX360_NAME_ID) )
            {
              DrawTexture(texXboxPad, 240, 100, DARKGRAY);

              //Draw buttons: xbox home
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE) ) DrawCircle(634, 189, 19, RED);

              //Draw buttons: basic 
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT) ) DrawCircle(676, 250, 9, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT) ) DrawCircle(592, 250, 9, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) ) DrawCircle(741, 251, 15, BLUE);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ) DrawCircle(776, 287, 15, LIME);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) ) DrawCircle(812, 251, 15, MAROON);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_UP) ) DrawCircle(776, 215, 15, GOLD);

              //Draw buttons: d-pad
              DrawRectangle(557, 302, 19, 71, BLACK);
              DrawRectangle(533, 328, 69, 19, BLACK);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP) ) DrawRectangle(557, 302, 19, 26, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ) DrawRectangle(557, 347, 19, 26, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ) DrawRectangle(532, 328, 26, 19, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ) DrawRectangle(576, 328, 26, 19, RED);

              //Draw buttons: left-right back
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) DrawCircle(499, 161, 20, RED);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) DrawCircle(776, 161, 20, RED);
 
              //Draw axis: left joystick
              DrawCircle(499, 252, 39, BLACK);
              DrawCircle(499, 252, 34, LIGHTGRAY);
              DrawCircle(499 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) * 20),
                         252 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) * 20), 25, BLACK);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_THUMB) )
              {
                DrawCircle(499 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) * 20),
                           252 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) * 20 ), 25, RED);
              }
 
              //Draw axis: right joystick
              DrawCircle(701, 337, 38, BLACK);
              DrawCircle(701, 337, 33, LIGHTGRAY);
              DrawCircle(701 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_X) * 20),
                         337 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, BLACK);
              if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_THUMB) )
              {
                DrawCircle(701 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_X) * 20),
                           337 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_Y) * 20 ), 25, RED);
              }

              //Draw axis: left-right triggers 
              DrawRectangle(410, 130, 15, 70, GRAY);
              DrawRectangle(844, 130, 15, 70, GRAY);
              DrawRectangle(410, 130, 15, (((1.0f + GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2.0f) * 70), RED);
              DrawRectangle(844, 130, 15, (((1.0f + GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2.0f) * 70), RED);

            }
            else if (IsGamepadName(GAMEPAD_PLAYER1, PS3_NAME_ID) || IsGamepadName(GAMEPAD_PLAYER1, SHANWAN_NAME_ID) )
            {
                //Draw the ps3 texture
                DrawTexture(texPs3Pad, 240, 100, DARKGRAY);

                //Draw buttons: ps
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE) ) DrawCircle(636, 322, 13, RED);

                //Draw buttons: basic
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT) ) DrawRectangle(568, 270, 32, 13, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT) ) DrawTriangle((Vector2){ 676, 268}, (Vector2){ 676, 285}, (Vector2){ 704, 277}, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_UP) ) DrawCircle(797, 244, 13, LIME);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ) DrawCircle(797, 303, 13, VIOLET);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) ) DrawCircle(826, 273, 13, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) ) DrawCircle(767, 273, 13, PINK);

                //Draw buttons: d-pad
                DrawRectangle(465, 232, 24, 84, BLACK);
                DrawRectangle(435, 261, 84, 25, BLACK);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(465, 232, 24, 29, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(465, 286, 24, 30, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(435, 262, 30, 25, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(490, 262, 30, 25, RED);

                //Draw buttons: left-right back buttons
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1) ) DrawCircle(479, 182, 20, RED);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) ) DrawCircle(797, 182, 20, RED);

                //Draw axis: left joystick
                DrawCircle(559, 355, 35, BLACK);
                DrawCircle(559, 355, 31, LIGHTGRAY);
                DrawCircle(559 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) * 20),
                           355 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) * 20 ), 25, BLACK);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_THUMB) )
                {
                    DrawCircle(559 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) * 20),
                          355 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) * 20 ), 25, RED);
                }
 
                //Draw axis: right joystick
                DrawCircle(715, 355, 35, BLACK);
                DrawCircle(715, 355, 31, LIGHTGRAY);
                DrawCircle(715 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_X) * 20 ),
                           355 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, BLACK);
                if( IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_THUMB) )
                {
                    DrawCircle(715 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_X) * 20 ),
                              355 + ( GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, RED);
                } 

                //Draw axis: left-right triggers
                DrawRectangle(409, 148, 15, 70, GRAY);
                DrawRectangle(851, 148, 15, 70, GRAY);
                DrawRectangle(409, 148, 15, (((1.0f - GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2.0f) * 70), RED);
                DrawRectangle(851, 148, 15, (((1.0f - GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2.0f) * 70), RED);

            }
            else
            {
              DrawText("- GENERIC GAMEPAD -", 520, 280, 20, GRAY);

              //TODO: Draw generic gamepad
            }

            DrawText(TextFormat("DETECTED AXIS [%i]:", GetGamepadAxisCount(GAMEPAD_PLAYER1)), 10, 50, 10, MAROON);

            for( int i = 0; i < GetGamepadAxisCount(GAMEPAD_PLAYER1); i++)
            {
              DrawText(TextFormat("AXIS %i: %.02f", i, GetGamepadAxisMovement(GAMEPAD_PLAYER1, i)), 20, 70 + 20 * i, 10, DARKGRAY);
            }

            if( GetGamepadButtonPressed() != -1) DrawText(TextFormat("DETECTED BUTTON: %i", GetGamepadButtonPressed()), 10, 430, 10, RED);
        }
        else
        {
            //Print text to screen (text, posX, posY, Size, Color);
            DrawText("GP1: NOT DETECTED", 10, 10, 10, GRAY);

            //Draw a texture (textureName, posX, posY, Color);
            DrawTexture(texXboxPad, 240, 100, LIGHTGRAY);
        }

	DrawFPS(0, 0);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(texPs3Pad);
    UnloadTexture(texXboxPad);

    //Clear
    CloseWindow();

    return 0;
}

