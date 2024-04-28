#include "Enemy.h"
#include "raymath.h"
#include <iostream>

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex) : currentTexture(idleTex),
                                                                 runTexture(runTex),
                                                                 worldPosition(pos)
{
    width = currentTexture.width / maxFrames;
    height = currentTexture.height;
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{
        .x = screenPosition.x,
        .y = screenPosition.y,
        .width = currentTexture.width * characterScale,
        .height = currentTexture.height * characterScale};
}

void Enemy::undoMovement()
{
    worldPosition = lastFrameWorldPosition;
}

void Enemy::tick(float dT)
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
        .width = width * characterScale,
        .height = height * characterScale,
    };
    DrawTexturePro(currentTexture, source, destination, Vector2{0.0, 0.0}, 0.f, WHITE);
}
