/**
 *
 * This example show VR simulator in a 3D enviroment (VR is not C99)
 *
 * */

#ifdef OSX
#include "../lib/raylib.h"
#else
#include <raylib.h>
#endif

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
    // VR device parameters definition
    VrDeviceInfo device = {
            // Oculus Rift CV1 parameters for simulator
            .hResolution = 2160,                 // Horizontal resolution in pixels
            .vResolution = 1200,                 // Vertical resolution in pixels
            .hScreenSize = 0.133793f,            // Horizontal size in meters
            .vScreenSize = 0.0669f,              // Vertical size in meters
            .vScreenCenter = 0.04678f,           // Screen center in meters
            .eyeToScreenDistance = 0.041f,       // Distance between eye and display in meters
            .lensSeparationDistance = 0.07f,     // Lens separation distance in meters
            .interpupillaryDistance = 0.07f,     // IPD (distance between pupils) in meters

            // NOTE: CV1 uses fresnel-hybrid-asymmetric lenses with specific compute shaders
            // Following parameters are just an approximation to CV1 distortion stereo rendering
            .lensDistortionValues[0] = 1.0f,     // Lens distortion constant parameter 0
            .lensDistortionValues[1] = 0.22f,    // Lens distortion constant parameter 1
            .lensDistortionValues[2] = 0.24f,    // Lens distortion constant parameter 2
            .lensDistortionValues[3] = 0.0f,     // Lens distortion constant parameter 3
            .chromaAbCorrection[0] = 0.996f,     // Chromatic aberration correction parameter 0
            .chromaAbCorrection[1] = -0.004f,    // Chromatic aberration correction parameter 1
            .chromaAbCorrection[2] = 1.014f,     // Chromatic aberration correction parameter 2
            .chromaAbCorrection[3] = 0.0f,       // Chromatic aberration correction parameter 3
    };

    // Load VR stereo config for VR device parameteres (Oculus Rift CV1 parameters)
    VrStereoConfig config = LoadVrStereoConfig(device);

    // Distortion shader (uses device lens distortion and chroma)
    Shader distortion = LoadShader(0, TextFormat("resources/distortion%i.fs", GLSL_VERSION));

    // Update distortion shader with lens and distortion-scale parameters
    SetShaderValue(distortion, GetShaderLocation(distortion, "leftLensCenter"),
                   config.leftLensCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "rightLensCenter"),
                   config.rightLensCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "leftScreenCenter"),
                   config.leftScreenCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "rightScreenCenter"),
                   config.rightScreenCenter, SHADER_UNIFORM_VEC2);

    SetShaderValue(distortion, GetShaderLocation(distortion, "scale"),
                   config.scale, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "scaleIn"),
                   config.scaleIn, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "deviceWarpParam"),
                   device.lensDistortionValues, SHADER_UNIFORM_VEC4);
    SetShaderValue(distortion, GetShaderLocation(distortion, "chromaAbParam"),
                   device.chromaAbCorrection, SHADER_UNIFORM_VEC4);

    // Initialize framebuffer for stereo rendering
    // NOTE: Screen size should match HMD aspect ratio
    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 2.0f, 5.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    //Set Frames per second
    SetTargetFPS(fps);

    //This is the Game Main Loop
    while (!WindowShouldClose()) //Detect window close button or ESC key
    {
        UpdateCamera(&camera);          // Update camera (simulator mode)
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            BeginVrStereoMode(config);
            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                DrawGrid(40, 1.0f);

            EndMode3D();
            EndVrStereoMode();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(distortion);
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width,
                                                    (float)-target.texture.height }, (Vector2){ 0.0f, 0.0f }, WHITE);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
    }

    //Clean memory
    UnloadVrStereoConfig(config);   // Unload stereo config

    UnloadRenderTexture(target);    // Unload stereo render fbo
    UnloadShader(distortion);       // Unload distortion shader

    //Clear
    CloseWindow();

    return 0;
}

