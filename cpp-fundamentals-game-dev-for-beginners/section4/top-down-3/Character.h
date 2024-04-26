#include "raylib.h"

class Character
{
public:
    Character(int windowWidth, int windowHeight);
    void tick(float dT);
    Vector2 getWorldPosition() { return worldPosition; };
    void undoMovement();

private:
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
    float characterWidth{};
    float characterHeight{};
    Vector2 lastFrameWorldPosition{};
    float characterScale = 4.f;
};