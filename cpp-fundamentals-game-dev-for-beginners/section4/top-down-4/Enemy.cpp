#include "Enemy.h"
#include "raymath.h"
#include <iostream>

// on enemy ai
// in general a vector from a source location to a destination location = position vector of destination - position vector of source

Enemy::Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex)
{
    width = currentTexture.width / maxFrames;
    height = currentTexture.height;

    currentTexture = idleTex;
    speed = 3.5f;
}

void Enemy::tick(float dT)
{

    // get toTarget vector
    velocity = Vector2Subtract(target->getScreenPosition(), screenPosition);
    screenPosition = Vector2Subtract(worldPosition, target->getWorldPosition());
    BaseCharacter::tick(dT);
}

void Enemy::setTarget(Character *character)
{
    target = character;
}
