#include "raylib.h"

int main() {
    const int windoeWidth = 384;
    const int windowHeight = 384;

    InitWindow(windoeWidth, windowHeight,"tops");


    Texture2D map = LoadTexture("tileset/map1.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);



        Vector2 mapPosition{0.0,0.0};
        DrawTextureEx(map, mapPosition,0.0,4.0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    
}

