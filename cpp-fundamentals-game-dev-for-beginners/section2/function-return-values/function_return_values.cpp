
#include "raylib.h"

int main()
{
    InitWindow(350, 250, "test");

    while (WindowShouldClose()== false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}