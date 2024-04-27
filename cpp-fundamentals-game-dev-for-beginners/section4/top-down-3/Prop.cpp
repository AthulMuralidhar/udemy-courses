#include "Prop.h"
#include "raymath.h"
Prop::Prop(Vector2 vec, Texture2D tex) : worldPosition(vec),
                                         texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    // world position is where the  prop will be located in the world of the game - this might be outside the screen
    // that the player sees
    // 
    // screen position  is where tje prop appears relative to the top left corner of the screen (the window the player sees)

    
    Vector2 screenPosition = Vector2Subtract(worldPosition, knightPos);
    DrawTextureEx(texture, screenPosition, 0.f, propScale, WHITE);
}