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
    const float mapScale{4.f};

    Character knight(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the map
        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        // render knight
        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPosition().x < 0.f ||
            knight.getWorldPosition().y < 0.f ||
            knight.getWorldPosition().x + windowWidth > map.width * mapScale ||
            knight.getWorldPosition().y + windowHeight > map.height * mapScale
        )
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    UnloadTexture(map);
    // UnloadTexture(knightIdle);
    // UnloadTexture(knightRun);
    CloseWindow();
}
