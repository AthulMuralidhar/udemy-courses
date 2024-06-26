#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"


class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTex, Texture2D runTex);
    virtual void tick(float dT) override;
    void setTarget(Character* character);

private:
    Character* target{};
};