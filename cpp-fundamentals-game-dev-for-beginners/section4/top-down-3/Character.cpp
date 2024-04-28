#include "Character.h"
#include "raymath.h"
#include <iostream>

Character::Character(int windowWidth, int windowHeight)
{
    // character only
    width = static_cast<float>(currentTexture.width) / maxFrames;
    height = static_cast<float>(currentTexture.height);

    // screen position == knight position
    screenPosition = {
        .x = windowWidth / 2.0f - scale * (0.5f * width), // centere the knight
        .y = windowHeight / 2.0f - scale * (0.5f * height),
    };
}

void Character::tick(float dT)
{
    Vector2 direction{}; // need to set the direction to 0 every tick
    lastFrameWorldPosition = worldPosition;

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
        // world position += direction
        worldPosition = Vector2Add(worldPosition, scaled);

        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        // set sprite sheet based on character's movement
        currentTexture = runTexture;
    }
    else
    {
        currentTexture = idleTexture;
    }

    // update animation frame
    runningTime += dT;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        currentFrame++;

        if (currentFrame > maxFrames)
            currentFrame = 0;
    }

    Rectangle source{
        .x = currentFrame * width,
        .y = 0.0,
        .width = rightLeft * width,
        .height = height,
    };

    Rectangle destination{
        .x = screenPosition.x,
        .y = screenPosition.y,
        .width = width * scale,
        .height = height * scale,
    };
    DrawTexturePro(currentTexture, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);
}
