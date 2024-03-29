
#include "raylib.h"

int main()
{   

    int width = 350;
    int height = 250;
    InitWindow(width, height, "test");

    int centreX = width / 2; 
    int centreY = height / 2;


    while (WindowShouldClose()== false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(centreX, centreY, 100, BLUE);
        EndDrawing();
    }
}