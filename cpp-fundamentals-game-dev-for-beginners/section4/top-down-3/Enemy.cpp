#include "Enemy.h"
#include "raymath.h"
#include <iostream>

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex)
{
    width = currentTexture.width / maxFrames;
    height = currentTexture.height;

    currentTexture = idleTex;
    runTexture = runTex;
    worldPosition = pos;
}

void Enemy::tick(float dT)
{
    screenPosition = Vector2Subtract(worldPosition, target->getWorldPosition());

    BaseCharacter::tick(dT);
}

void Enemy::setTarget(Character *character)
{
    target = character;
}
