/**
 *This example particles blending 
 *
 * */

#include <raylib.h>

#define MAX_PARTICLES 200

//Particle structure with basic data 
typedef struct {
  Vector2 position;
  Color color;
  float alpha;
  float size;
  float rotation;
  bool active;   // NOTE: Use it to activate/desactive particle
} Particle;

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Particles Blending");


    // Particles pool, reuse them!
    Particle mouseTail[MAX_PARTICLES] = { 0 };

    //Initialize particles 
    for( int i = 0; i < MAX_PARTICLES; i++)
    {
      mouseTail[i].position = (Vector2){ 0, 0 };
      mouseTail[i].color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
      mouseTail[i].alpha = 1.0f;
      mouseTail[i].size = (float) GetRandomValue(1, 30) / 20.0f;
      mouseTail[i].rotation = (float)GetRandomValue(0, 360);
      mouseTail[i].active = false;
    }

    float gravity = 3.0f;

    Texture2D smoke = LoadTexture("resources/spark_flame.png");

    int blending = BLEND_ALPHA;

    //Set Frames per second
    SetTargetFPS(fps); //is comented because FLAG_VSYNC_HINT

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        
        // Activate one particle every frame and Update active particless 
        // NOTE: Particles initial position should be mouse position when activated
        // NOTE: Particles fall down with gravity and rotation... and disappear after 2 seconds (alpha = 0)
        // NOTE: When a particle disappears, active = false and it can be reused
        for( int i = 0; i < MAX_PARTICLES; i++ )
        {
          if( !mouseTail[i].active )
          {
            mouseTail[i].active = true;
            mouseTail[i].alpha = 1.0f;
            mouseTail[i].position = GetMousePosition();
            i = MAX_PARTICLES;
          }
        }

        for( int i = 0; i < MAX_PARTICLES; i++  )
        {
          if( mouseTail[i].active )
          {
            mouseTail[i].position.y += gravity / 2;
            mouseTail[i].alpha -= 0.005f;
            
            if( mouseTail[i].alpha <= 0.0f ) mouseTail[i].active = false;

            mouseTail[i].rotation += 2.0f;
          }
        }

        if( IsKeyPressed(KEY_SPACE) )
        {
          if( blending == BLEND_ALPHA ) blending = BLEND_ADDITIVE;
          else blending = BLEND_ALPHA;
        }

        //StartDrawing
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginBlendMode(blending);

                //Draw active particles 
                for( int i = 0; i < MAX_PARTICLES; i++ )
                {
                    if( mouseTail[i].active )
                    {
                      DrawTexturePro(smoke, (Rectangle){ 0.0f, 0.0f, (float)smoke.width, (float)smoke.height },
                          (Rectangle){ mouseTail[i].position.x, mouseTail[i].position.y, smoke.width * mouseTail[i].size, smoke.height * mouseTail[i].size },
                          (Vector2){ (float)(smoke.width * mouseTail[i].size / 2.0f), (float)(smoke.height * mouseTail[i].size / 2.0f) }, mouseTail[i].rotation,
                          Fade(mouseTail[i].color, mouseTail[i].alpha));
                    }
                }

            EndBlendMode();

            DrawText("DEDICATED TO THE SUPREME GAYMASTER MARUCHAN!", 380, 20, 20, BLACK);

            if( blending == BLEND_ALPHA ) DrawText("ALPHA BLENDING", 490, screenHeight - 40, 20, BLACK);
            else DrawText("ADDITIVE BLENDING", 480, screenHeight - 40, 20, RAYWHITE);

            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory
    UnloadTexture(smoke);

    //Clear
    CloseWindow();

    return 0;
}

