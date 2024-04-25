#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    void setScreenPosition(int windowWidth, int windowHeight);
    void tick(float dT);

private:
    Texture2D currentTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D runTexture = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPosition{};
    Vector2 mapPosition{0.0, 0.0};
    Vector2 direction{0.0, 0.0};
    const float speed = 4.0; // 1 == facing right, -1 == facing left
    float rightLeft = 1.f;
};

void Character::setScreenPosition(int windowWidth, int windowHeight)
{
    // screen position == knight position
    screenPosition = {
        .x = windowWidth / 2.0f - (0.5f * (float)currentTexture.width / 6.0f), // centere the knight
        .y = windowHeight / 2.0f - (0.5f * currentTexture.height),
    };
}

void Character::tick(float dT)
{
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    // move the character around
    if (Vector2Length(direction) != 0.0)
    {
        Vector2 normalized = Vector2Normalize(direction);
        Vector2 scaled = Vector2Scale(normalized, speed);
        mapPosition = Vector2Subtract(mapPosition, scaled);

        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        // set sprite sheet based on character's movement
        currentTexture = runTexture;
    }
    else
    {
        // knight is not moving
        currentTexture = idleTexture;
    }
}

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "tops");

    const float speed = 4.0;

    Texture2D map = LoadTexture("tileset/map1.png");
    Vector2 mapPosition{0.0, 0.0};
    Vector2 direction{0.0, 0.0};

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight{};

    const float scaleForKnight = 4.0;
    // 1 == facing right, -1 == facing left
    float rightLeft = 1.f;

    // animation variables
    float runningTime{};
    const float updateTime = 1.f / 12.f;
    int currentFrame{};
    const int maxFrames = 6;

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
        if (Vector2Length(direction) != 0.0)
        {
            Vector2 normalized = Vector2Normalize(direction);
            Vector2 scaled = Vector2Scale(normalized, speed);
            mapPosition = Vector2Subtract(mapPosition, scaled);

            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            // set sprite sheet based on character's movement
            knight = knightRun;
        }
        else
        {
            // knight is not moving
            knight = knightIdle;
        }

        // draw the map
        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            runningTime = 0.f;
            currentFrame++;

            if (currentFrame > maxFrames)
                currentFrame = 0;
        }

        // draw the character
        Vector2 knightPosition{
            .x = windowWidth / 2.0f - (0.5f * (float)knight.width / 6.0f), // centere the knight
            .y = windowHeight / 2.0f - (0.5f * knight.height),
        };
        Rectangle source{
            .x = currentFrame * (float)knight.width / 6.0f,
            .y = 0.0,
            .width = rightLeft * (float)knight.width / 6.0f,
            .height = (float)knight.height,
        };

        Rectangle destination{
            .x = knightPosition.x,
            .y = knightPosition.y,
            .width = knight.width / 6.0f * scaleForKnight,
            .height = knight.height * scaleForKnight,
        };
        DrawTexturePro(knight, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knightIdle);
    UnloadTexture(knightRun);
    CloseWindow();
}
