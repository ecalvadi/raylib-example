/**
 * This example show a benchmark of 2D capabilities instancing a lot of bunnies on screen
 * 
 * */

#include <raylib.h>

#include <stdlib.h>                 // Required for: malloc(), free()

#define MAX_BUNNIES     100000      // 100k bunnies limit 

// This is the maximun amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
#define MAX_BATCH_ELEMENTS  8192

typedef struct Bunny {
    Vector2 position;
    Vector2 speed;
    Color color;
} Bunny;

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Bunnymark");

    // Load bunny texture
    Texture2D texBunny = LoadTexture("resources/wabbit_alpha.png");

    Bunny *bunnies = (Bunny *)malloc(MAX_BUNNIES*sizeof(Bunny)); // Bunnies array

    unsigned int bunniesCount = 0;  // Bunnies counter

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //Update
        if( IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
        {
            //  Create more bunnies 
            for ( unsigned int i = 0; i < 100; i++)
            {
                if (bunniesCount < MAX_BUNNIES)
                {
                    bunnies[bunniesCount].position = GetMousePosition();
                    bunnies[bunniesCount].speed.x = (float)GetRandomValue(-250, 250)/60.0f;
                    bunnies[bunniesCount].speed.y = (float)GetRandomValue(-250, 250)/60.0f;
                    bunnies[bunniesCount].color = (Color){ GetRandomValue(50, 240),
                                                        GetRandomValue(80, 240),
                                                        GetRandomValue(100, 240), 255};

                    ++bunniesCount;
                }
            }
        }

        //Update bunnies 
        for (unsigned int i = 0; i < bunniesCount; i++)
        {
            bunnies[i].position.x += bunnies[i].speed.x;
            bunnies[i].position.y += bunnies[i].speed.y;

            if(((bunnies[i].position.x + texBunny.width/2) > GetScreenWidth()) || 
                ((bunnies[i].position.x + texBunny.width/2) < 0)) bunnies[i].speed.x *= -1;
            if(((bunnies[i].position.y + texBunny.height/2) > GetScreenHeight()) || 
                ((bunnies[i].position.y + texBunny.height/2) < 40)) bunnies[i].speed.y *= -1;

        }

        //StartDrawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (unsigned int i = 0; i < bunniesCount; i++)
            {
                // NOTE: When internal batch buffer limit is reached (MAX_BATCH_ELEMENTS),
                // a draw call is launched and buffer starts beign filled again;
                // before issuing a draw call, updated vertex data from internal CPU buffer is send to GPU...
                // Process of sending data is costly and it could happen that GPU data has not been completely
                // processed for drawing while new data is tried to be sent (updating current in-use buffers)
                // it could generates a stall and consecuently a frame drop, limit the number of drawn bunnies
                DrawTexture(texBunny, (int)bunnies[i].position.x, (int)bunnies[i].position.y, bunnies[i].color);
            }

            DrawRectangle(0, 0, screenWidth, 40, BLACK);
            DrawText(TextFormat("bunnies: %i", bunniesCount), 120, 10, 20, GREEN);
            DrawText(TextFormat("batched draw calls: %i", 1 + bunniesCount/MAX_BATCH_ELEMENTS), 320, 10, 20, MAROON);
            DrawFPS(10, 10);

        EndDrawing();
    }

    //Clear

    UnloadTexture(texBunny);
    
    CloseWindow();

    return 0;
}

