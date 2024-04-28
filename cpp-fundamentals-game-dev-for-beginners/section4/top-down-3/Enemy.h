#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    void tick(float dT);
    Vector2 getWorldPosition() { return worldPosition; };
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D currentTexture{};
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
    float characterScale = 4.f;
};