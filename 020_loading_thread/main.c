/**
 *
 * This example show how to use threads
 *
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

#include <pthread.h>      //POSIX style threads management

#include <stdatomic.h>    //C11 atomic data types

#include <time.h>         //Required for: clock()


//Using C11 atomics for synchronization
//NOTE: A plain bool ( or any plain data type for that matter) cant' be used dor inter-thread synchronization 
static atomic_bool dataLoaded = ATOMIC_VAR_INIT(false); //Data Loaded completion indicator
static void *LoadDataThread(void *arg);                 //Loading data thread function declaration

static int dataProgress = 0;                            //Data progress accumulator

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - Loading Thread");

    pthread_t threadId;       //Loading data thread id

    enum { STATE_WAITING, STATE_LOADING, STATE_FINISHED } state = STATE_WAITING;
    int framesCounter = 0;

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        switch( state )
        {
          case STATE_WAITING:
          {
            if( IsKeyPressed(KEY_ENTER) )
            {
              int error = pthread_create(&threadId, NULL, &LoadDataThread, NULL);
              if( error != 0) TraceLog(LOG_ERROR, "Error creating loading thread");
              else TraceLog(LOG_INFO, "Loading thread initialized successfully");

              state = STATE_LOADING;
            }
          }break;
          case STATE_LOADING:
          {
            framesCounter++;
            if( atomic_load(&dataLoaded) )
            {
              framesCounter = 0;
              state = STATE_FINISHED;
            }
          } break;
          case STATE_FINISHED:
          {
            if( IsKeyPressed(KEY_ENTER) )
            {
              //Reset everything to launch again
              atomic_store(&dataLoaded, false);
              dataProgress = 0;
              state = STATE_WAITING;
            }
          } break;
          default: break;
        }

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          switch( state )
          {
            case STATE_WAITING: DrawText("PRESS ENTER to START LOADING DATA", 400, 270, 20, DARKGRAY); break;
            case STATE_LOADING:
            {
              DrawRectangle(400, 300, dataProgress, 60, SKYBLUE);
              if( (framesCounter / 15) % 2) DrawText("LOADING DATA...", 490, 310, 40, DARKBLUE);
            } break;
            case STATE_FINISHED:
            {
              DrawRectangle(400, 300, 500, 60, LIME);
              DrawText("DATA LOADED!", 500, 310, 40, GREEN);
            } break;
            default: break;
          }

          DrawRectangleLines(400, 300, 500, 60, DARKGRAY);


          DrawFPS(10, 10);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

//Loading data thread function definition
static void *LoadDataThread(void *arg)
{
  int timeCounter = 0;          //Time counted in ms
  clock_t prevTime = clock();   //Previous time

  //We simulate data loading with a time counter for 5 seconds
  while( timeCounter < 5000 )
  {
    clock_t currentTime = clock() - prevTime;
    timeCounter = (int)((float)currentTime * 1000 / CLOCKS_PER_SEC);

    //We accumulate time over a global variable to be used in
    //main thread as a progress bar
    dataProgress = timeCounter / 10;
  }

  //When data has finished loading, we set global variable 
  atomic_store(&dataLoaded, true);

  return NULL;

}
