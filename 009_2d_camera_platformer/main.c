/**
 *
 * This example show how works a 2D camera 
 *
 * */

#include <raylib.h>
#include <raymath.h>

//Gravity
#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

//Define Player struct 
typedef struct Player {
  Vector2 position;
  float speed;
  bool canJump;
} Player;

typedef struct EnvItem {
  Rectangle rect;
  int blocking;
  Color color;
} EnvItem;

typedef enum GamePad {
    GAMEPAD_PLAYER1,
} GamePad;
//Function declarations 
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);

//camera updates 
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraEvenOutOnLanding(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);


int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 2D Camera Platformer");

    //Initialization of player 
    Player player = { 0 };
    player.position = (Vector2){ 600, 680 };
    player.speed = 0;
    player.canJump = false;

    //Platforms initializations
    EnvItem envItems[] = {
      { { 0, 0, 2000, 800 }, 0, LIGHTGRAY },
      { { 0, 800, 2000, 200 }, 1, GRAY },
      { { 300, 200, 300, 10 }, 1, GRAY },
      { { 250, 300, 100, 10 }, 1, GRAY },
      { { 650, 300, 100, 10 }, 1, GRAY },
      { { 870, 400, 100, 10 }, 1, GRAY },
      { { 950, 600, 100, 10 }, 1, GRAY },
      { { 950, 550, 100, 10 }, 1, GRAY },
      { { 1050, 600, 100, 10 }, 1, GRAY },
      { { 850, 650, 200, 10 }, 1, GRAY },
   
    };

    int envItemsLength = sizeof(envItems) / sizeof(envItems[0]);

    //Initialization of camera
    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //Store pointers to the multiple update camera functions (TODO: view this later!!! its so cool)
    void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
      UpdateCameraCenter,
      UpdateCameraCenterInsideMap,
      UpdateCameraCenterSmoothFollow,
      UpdateCameraEvenOutOnLanding,
      UpdateCameraPlayerBoundsPush
    };

    int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters) / sizeof(cameraUpdaters[0]);

    char *cameraDescriptions[] = {
      "Follow player center",
      "Follow player center, but clamp to map edges",
      "Follow player center; smoothed",
      "Follow player center horizontally; updateplayer center vertically after landing",
      "Player push camera on getting too close to screen edge"
    };

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        float deltaTime = GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        camera.zoom += ( (float)GetMouseWheelMove() * 0.05f );

        if( camera.zoom > 3.0f ) camera.zoom = 3.0f;
        else if( camera.zoom < 0.25f ) camera.zoom = 0.25f;

        if( IsKeyPressed(KEY_R) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1) )
        {
          camera.zoom = 1.0f;
          player.position = (Vector2){ 400, 280 };
        }

        if( IsKeyPressed(KEY_C) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1) ) cameraOption = ( cameraOption + 1 ) % cameraUpdatersLength;

        //Call update camera function by its pointer
        cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);

        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginMode2D(camera);

            //Draw the blocks (floor and platforms)
            for( int i = 0; i < envItemsLength; i++ ) DrawRectangleRec(envItems[i].rect, envItems[i].color);

            //Draw player
            Rectangle playerRec = { player.position.x -20, player.position.y -40, 40, 40 };
            DrawRectangleRec(playerRec, RED);

          EndMode2D();

          DrawText("Controls:", 20, 20, 10, BLACK);
          DrawText("- Right/Left", 40, 40, 10, DARKGRAY);
          DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
          DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
          DrawText("- C to change camera mode", 40, 100, 10, DARKGRAY);
          DrawText("Current camera mode:", 20, 120, 10, BLACK);
          DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);

	  DrawFPS(0, 0);

        EndDrawing();
    }

    //Clean memory

    //Clear
    CloseWindow();

    return 0;
}

//Implementation of UpdatePlayer Function
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
  //Player movement
  //TODO: ADD Joystick Support
  if( IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ) player->position.x -= PLAYER_HOR_SPD * delta;
  if( IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ) player->position.x += PLAYER_HOR_SPD * delta;
  if( (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) && player->canJump )
  {
    player->speed = -PLAYER_JUMP_SPD;
    player->canJump = false;
  }

  //Obstacles
  //Review in more details later
  int hintObstacle = 0;
  for( int i = 0; i < envItemsLength; i++ )
  {
    EnvItem *ei = envItems + i;
    Vector2 *p = &(player->position);
    if( ei->blocking &&
        ei->rect.x <= p->x &&
        ei->rect.x + ei->rect.width >= p->x &&
        ei->rect.y >= p->y &&
        ei->rect.y < p->y + player->speed * delta )
    {
      hintObstacle = 1;
      player->speed = 0.0f;
      p->y = ei->rect.y;
    }
  }

  if( !hintObstacle )
  {
    player->position.y += player->speed * delta;
    player->speed += G * delta;
    player->canJump = false;
  }
  else player->canJump = true;

}

//Implementation of UpdateCameraCenter Function. 
//clran envItems, envItemsLength and delta
void UpdateCameraCenter(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
  camera->offset = (Vector2){ (float)width / 2, (float)height / 2 };
  camera->target = player->position;
}

//Implementation of UpdateCameraCenterInsideMap Function.
void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
  camera->target = player->position;
  camera->offset = (Vector2){ (float)width / 2, (float)height / 2 };
  float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

  //Find min and max values?
  for( int i = 0; i < envItemsLength; i++ )
  {
    EnvItem *ei = envItems + 1;
    minX = fminf(ei->rect.x, minX);
    maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
    minY = fminf(ei->rect.y, minY);
    maxY = fmaxf(ei->rect.y + ei->rect.height, minY);
  }

  //TODO: Investigate GetWorldToScreen2D 
  Vector2 max = GetWorldToScreen2D( (Vector2){maxX, maxY}, *camera );
  Vector2 min = GetWorldToScreen2D( (Vector2){minX, minY}, *camera );

  //TODO: review this
  if( max.x < (float)width ) camera->offset.x = (float)width - (max.x - (float)width / 2);
  if( max.y < (float)height ) camera->offset.y = (float)height - (max.y - (float)height / 2) ;
  if( min.x > 0 ) camera->offset.x = (float)width / 2 - min.x;
  if( min.y > 0 ) camera->offset.y = (float)height / 2 - min.y;
}

//Implementation of UpdateCameraCenterSmoothFollow Function.
void UpdateCameraCenterSmoothFollow(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
  static float minSpeed = 30;
  static float minEffectLength = 10;
  static float fractionSpeed = 0.8f;

  camera->offset = (Vector2){ (float)width / 2, (float)height / 2};
  Vector2 diff = Vector2Subtract( player->position, camera->target );
  float length = Vector2Length(diff);

  if( length > minEffectLength )
  {
    float speed = fmaxf( fractionSpeed * length, minSpeed );
    camera->target = Vector2Add( camera->target, Vector2Scale(diff, speed * delta / length) );
  }
}

//Implementation of UpdateCameraEvenOutOnLanding Function.
void UpdateCameraEvenOutOnLanding(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
  static float evenOutSpeed = 700;
  static int eveningOut = false;
  static float evenOutTarget;

  camera->offset = (Vector2){ (float)width / 2, (float)height / 2 };
  camera->target.x = player->position.x;

  if( eveningOut )
  {
    if( evenOutTarget > camera->target.y )
    {
      camera->target.y += evenOutSpeed * delta;

      if( camera->target.y > evenOutTarget )
      {
        camera->target.y = evenOutTarget;
        eveningOut = 0;
      }
    }
    else 
    {
      camera->target.y -= evenOutSpeed * delta;

      if( camera->target.y < evenOutTarget )
      {
        camera->target.y = evenOutTarget;
        eveningOut = 0;
      }
    }
  }
  else 
  {
    if( player->canJump && (player->speed == 0) && (player->position.y != camera->target.y) )
    {
      eveningOut = 1;
      evenOutTarget = player->position.y;
    }
  }
}

//Implementation of UpdateCameraPlayerBoundsPush Function
void UpdateCameraPlayerBoundsPush(Camera2D * camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
  static Vector2 bbox = { 0.2f, 0.2f };

  Vector2 bboxWorldMin = GetScreenToWorld2D( (Vector2){ (1 - bbox.x) * 0.5f * (float)width, (1 - bbox.y) * 0.5f * (float)height }, *camera );
  Vector2 bboxWorldMax = GetScreenToWorld2D( (Vector2){ (1 + bbox.x) * 0.5f * (float)width, (1 + bbox.y) * 0.5f * (float)height }, *camera );
  camera->offset = (Vector2){ (1 - bbox.x) * 0.5f * (float)width, (1 - bbox.y) * 0.5f * (float)height };

  if( player->position.x < bboxWorldMin.x ) camera->target.x = player->position.x;
  if( player->position.y < bboxWorldMin.y ) camera->target.y = player->position.y;
  if( player->position.x > bboxWorldMax.x ) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
  if( player->position.y > bboxWorldMax.y ) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);

}


