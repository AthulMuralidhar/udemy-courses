#include "raylib.h"
#include "raymath.h"

// movement
// - movement in the game is achieved by moving the map (our map texture) around rather than the character

int main()
{
    const int windoeWidth = 384;
    const int windowHeight = 384;
    InitWindow(windoeWidth, windowHeight, "tops");

    const float speed = 4.0;

    Texture2D map = LoadTexture("tileset/map1.png");
    Vector2 mapPosition{0.0, 0.0};
    Vector2 direction{0.0, 0.0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        // move the map around
        if (Vector2Length(direction) != 0.0) // only move the vector if the direction is unchanged
        {
            Vector2 normalized = Vector2Normalize(direction); // we want to keep the direction normalized so that there is no extra unwanted movenet
            // knowthing the direction, we now need to move the map in the opposite direction:
            // mapPosition = mapPosition - direction
            // we also need to scale the vector as the usual movement is slow
            Vector2 scaled = Vector2Scale(normalized, speed);
            mapPosition = Vector2Subtract(mapPosition, scaled);
        }

        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
