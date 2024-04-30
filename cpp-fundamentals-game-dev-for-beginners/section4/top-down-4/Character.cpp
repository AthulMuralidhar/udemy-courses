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

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(dT);
}
