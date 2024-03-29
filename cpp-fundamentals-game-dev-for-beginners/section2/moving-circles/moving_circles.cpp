
#include "raylib.h"

int main()
{

    // window coordinates
    int width = 350;
    int height = 250;
    InitWindow(width, height, "test");

    // circle coordinates
    int centreX = width / 2;
    int centreY = height / 2;
    int circleRadius = 10;
    int fps = 60;
    Color circleColor = BLUE;

    SetTargetFPS(fps);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic begins
        DrawCircle(centreX, centreY, circleRadius, circleColor);

        if (IsKeyDown(KEY_D) && centreX < width) {
            centreX += 1;
            // no need to redraw as the while loop just continues to execute
        }

        if (IsKeyDown(KEY_A) && centreX > 0) {
            centreX -= 1;
        }

        if (IsKeyDown(KEY_W) && centreY > 0) {
            centreY -=1;
        }

        if (IsKeyDown(KEY_S) && centreY < height) {
            centreY += 1;
        }


        // game logic ends

        EndDrawing();
    }
}
