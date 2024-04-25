#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "tops");

    Texture2D map = LoadTexture("tileset/map1.png");
    Vector2 mapPosition{0.0, 0.0};

    Character knight;
    knight.setScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the map
        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
    // UnloadTexture(knightIdle);
    // UnloadTexture(knightRun);
    CloseWindow();
}
