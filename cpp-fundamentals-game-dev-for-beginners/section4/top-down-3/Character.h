#include "raylib.h"

class Character
{
public:
    Character();
    void setScreenPosition(int windowWidth, int windowHeight);
    void tick(float dT);
    Vector2 getWorldPosition() { return worldPosition; };

private:
    Texture2D currentTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D runTexture = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPosition{};        // upper left corner of the character rectangle
    Vector2 worldPosition{0.0, 0.0}; // upper left corner of the world / window
    Vector2 direction{0.0, 0.0};
    const float speed = 4.0;
    // 1 == facing right, -1 == facing left
    float rightLeft = 1.f;
    // animation variables
    float runningTime{};
    const float updateTime = 1.f / 12.f;
    int currentFrame{};
    const int maxFrames = 6;
    const float scaleForCharacter = 4.0;
    float characterWidth{};
    float characterHeight{};
};