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
