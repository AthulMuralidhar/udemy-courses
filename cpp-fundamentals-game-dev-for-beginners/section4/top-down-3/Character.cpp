#include "Character.h"
#include "raymath.h"
#include <iostream>

Character::Character(int windowWidth, int windowHeight)
{
    // character only
    characterWidth = static_cast<float>(currentTexture.width) / maxFrames;
    characterHeight = static_cast<float>(currentTexture.height);

    // screen position == knight position
    screenPosition = {
        .x = windowWidth / 2.0f - characterScale * (0.5f * characterWidth), // centere the knight
        .y = windowHeight / 2.0f - characterScale * (0.5f * characterHeight),
    };
}

Rectangle Character::getCollisionRec() {
    return Rectangle{
        .x = screenPosition.x,
        .y = screenPosition.y,
        .width = currentTexture.width * characterScale,
        .height = currentTexture.height * characterScale
    };
}

void Character::undoMovement()
{
    worldPosition = lastFrameWorldPosition;
}

void Character::tick(float dT)
{   
    Vector2 direction{};  // need to set the direction to 0 every tick 
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
        .x = currentFrame * characterWidth,
        .y = 0.0,
        .width = rightLeft * characterWidth,
        .height = characterHeight,
    };

    Rectangle destination{
        .x = screenPosition.x,
        .y = screenPosition.y,
        .width = characterWidth * characterScale,
        .height = characterHeight * characterScale,
    };
    DrawTexturePro(currentTexture, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);
}
