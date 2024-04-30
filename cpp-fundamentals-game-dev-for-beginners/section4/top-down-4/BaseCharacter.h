#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPosition() { return worldPosition; };
    Vector2 getScreenPosition() { return screenPosition; };
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float dT);

protected:
    Texture2D currentTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D runTexture = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPosition{};        // upper left corner of the character rectangle
    Vector2 worldPosition{0.0, 0.0}; // upper left corner of the world / window
    float speed = 4.0;
    // 1 == facing right, -1 == facing left
    float rightLeft = 1.f;
    // animation variables
    float runningTime{};
    float updateTime = 1.f / 12.f;
    int currentFrame{};
    int maxFrames = 6;
    float width{};
    float height{};
    Vector2 lastFrameWorldPosition{};
    float scale = 4.f;
    Vector2 velocity{};
};

#endif