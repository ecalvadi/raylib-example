/**
 *
 * This example show VR simulator in a 3D enviroment 
 *
 * */

#include <raylib.h>

#if defined(PLATFORM_DESKTOP)
  #define GLSL_VERSION    330
#else //PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
  #define GLSL_VERSION    100
#endif

int main(void) {
    //Initialization of the screen resolution
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int fps = 60; // Set the FPS Here for later calc of velocity
    //int speed = (fps == 60) ? 2 : 4;

    //NOTE: screenWidth/screenHeight should match VR device aspect ratio

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    //Initialization of the main window, passing the screen width
    //and height constants, finally we added a title of the window.
    InitWindow(screenWidth, screenHeight, "ÑirEngine 0.1 ALPHA - 3D VR Simulator");

    //Init VR simulator (Pciñis Roft CV1 parameters)
    InitVrSimulator();

    VrDeviceInfo hmd = { 0 };   //VR device parameters (head-mounted-devide)

    //Oculus Rift CV1 parameters for simulator
    hmd.hResolution = 2160;                 //HMD horizontal resolution in pixels
    hmd.vResolution = 1200;                 //HMD vertical resolution in pixels
    hmd.hScreenSize = 0.133793f;            //HMD horizontal size in meters
    hmd.vScreenSize = 0.0669f;              //HMD vertical size in meters
    hmd.vScreenCenter = 0.04678f;           //HMD screen center in meters
    hmd.eyeToScreenDistance = 0.041f;       //HMD distance between eye and display in meters
    hmd.lensSeparationDistance = 0.07f;     //HMD lens separation distance in meters
    hmd.interpupillaryDistance = 0.07f;     //HMD IPD (distance between pupils) in meters

    //NOTE: CV1 uses a Fresnel-hybrid-asymmetric lenses with specific distortion compute shaders.
    //Following parameters are an approximation to distortion stereo rendering but results differ from actual devide
    hmd.lensDistortionValues[0] = 1.0f;     //HMD lens distortion constant parameter 0 
    hmd.lensDistortionValues[1] = 0.22f;    //HMD lens distortion constant parameter 1
    hmd.lensDistortionValues[2] = 0.24f;    //HMD lens distortion constant parameter 2
    hmd.lensDistortionValues[3] = 0.0f;     //HMD lens distortion constant parameter 3
    hmd.chromaAbCorrection[0] = 0.996f;     //HMD chromatic aberration correction parameter 0 
    hmd.chromaAbCorrection[1] = -0.004f;    //HMD chromatic aberration correction parameter 1
    hmd.chromaAbCorrection[2] = 1.014f;     //HMD chromatic aberration correction parameter 2
    hmd.chromaAbCorrection[3] = 0.0f;       //HMD chromatic aberration correction parameter 3

    //Distortion shader (uses device lens distortion and chroma)
    Shader distortion = LoadShader(0, TextFormat("resources/distortion%i.fs", GLSL_VERSION));

    SetVrConfiguration(hmd, distortion); //Set Vr device parameters for stereo rendering 

    //Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 2.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        //TODO: Update variables of the game loop
        UpdateCamera(&camera);

        if( IsKeyPressed(KEY_SPACE) ) ToggleVrMode();

        //StartDrawing
        BeginDrawing();

          ClearBackground(RAYWHITE);

          BeginVrDrawing();
            BeginMode3D(camera);

              DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
              DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

              DrawGrid(40, 1.0f);

            EndMode3D();

          EndVrDrawing();

          DrawFPS(10, 10);


        EndDrawing();
    }

    //Clean memory
    UnloadShader(distortion);

    CloseVrSimulator();

    //Clear
    CloseWindow();

    return 0;
}

