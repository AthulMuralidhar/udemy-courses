#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        .x = screenPosition.x,
        .y = screenPosition.y,
        .width = currentTexture.width * scale,
        .height = currentTexture.height * scale};
}

void BaseCharacter::undoMovement()
{
    worldPosition = lastFrameWorldPosition;
}

void BaseCharacter::tick(float dT)
{
    lastFrameWorldPosition = worldPosition;

    // update animation frame
    runningTime += dT;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        currentFrame++;

        if (currentFrame > maxFrames)
            currentFrame = 0;
    }

    // update movement
    if (Vector2Length(velocity) != 0.0)
    {
        Vector2 velocity = Vector2Normalize(velocity);
        Vector2 scaled = Vector2Scale(velocity, speed);
        // world position += direction
        worldPosition = Vector2Add(worldPosition, scaled);

        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        // set sprite sheet based on character's movement
        currentTexture = runTexture;
    }
    else
    {
        currentTexture = idleTexture;
    }
    velocity = {}; // reset velocity as it is updated each frame (each tick)

    // draw character
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