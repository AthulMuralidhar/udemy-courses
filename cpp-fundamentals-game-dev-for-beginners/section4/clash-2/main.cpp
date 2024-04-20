#include "raylib.h"

// NOTE: should select gcc as a compiler found in /usr
//cmd to run: g++ main.cpp  -I"~/raylib" -L"~/raylib/lib" -lraylib  


// problem:
// getting seg faults during loadtexture
// the initi windoe goes through and that is no problem somehow
// only the loadtexture  line causes issues

// try1
// checked other prev files to see if the const addition to texture 2d has an effect
// it does not

// try2 
// switched my tileset with the course 's one, 
// still seg faults



int main() {
   // window coordinates
   const int windowDimensions[2] = {384,384};
   // frames per sec
   const int fps = 60;

   // textures
    Texture2D mapTexture = LoadTexture("./tileset/map1.png");
    // Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

   // initialise window
    InitWindow(windowDimensions[0], windowDimensions[1], "top downz");


    // map position
    Vector2 mapPosition{0.0,0.0};


    SetTargetFPS(fps);
    // Game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);


        // DrawTextureEx(mapTexture,mapPosition,0.0,4.0,WHITE);

        EndDrawing();
    }



    // UnloadTexture(mapTexture);

    CloseWindow();

}