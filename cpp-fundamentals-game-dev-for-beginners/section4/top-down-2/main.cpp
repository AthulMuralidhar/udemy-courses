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

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPosition{
        .x = windoeWidth / 2.0f - (0.5f * (float)knight.width / 6.0f), // we want the knight to be in the centre of the screen
        .y = windowHeight / 2.0f - (0.5f * knight.height),
    };
    const float scaleForKnight = 4.0;
    // 1 == facing right, -1 == facing left
    // this allows us to turn the sprite sheet for the knight so that he faces the appropriate direction
    float rightLeft = 1.f;

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

            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }

        // draw the map
        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);

        // draw the character
        Rectangle source{
            .x = 0.0,
            .y = 0.0,
            // if we multiply the width by -1 we get the source texture flipped
            .width = rightLeft * (float)knight.width / 6.0f, // as there are 6 sprites in the sprite sheet
            .height = (float)knight.height,
        };

        Rectangle destination{
            .x = knightPosition.x,
            .y = knightPosition.y,
            .width = knight.width / 6.0f * scaleForKnight, // as there are 6 sprites in the sprite sheet
            .height = knight.height * scaleForKnight,
        };
        DrawTexturePro(knight, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
