#include "BaseCharacter.h"

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