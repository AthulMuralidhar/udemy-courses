#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "tops");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{4.f};

    // init character
    Character knight{windowWidth, windowHeight};

    // init props
    Prop props[2]{
        {Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        {Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    // init  enemy
    Enemy goblin{Vector2{}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the map
        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        // render rock
        // rock.Render(knight.getWorldPosition());

        // render props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPosition());
        }

        // render knight
        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPosition().x < 0.f ||
            knight.getWorldPosition().y < 0.f ||
            knight.getWorldPosition().x + windowWidth > map.width * mapScale ||
            knight.getWorldPosition().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check for prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPosition()), knight.getCollisionRec()))
                knight.undoMovement();
        }

        // draw enemy
        goblin.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
    // UnloadTexture(knightIdle);
    // UnloadTexture(knightRun);
    CloseWindow();
}
