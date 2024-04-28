#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    virtual void tick(float dT) override;

private:
};