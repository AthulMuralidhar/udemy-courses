
#include "raylib.h"

int main() {
    // window coordinates
    const int windowWidth = 512;
    const int windowHeight = 380;
    int fps = 60;
    // initialise window
    InitWindow(windowWidth, windowHeight, "dasher");


    // retangle coordinates
    const int rectWidth = 50;
    const int rectHeight = 80;/* condition *//* condition */
    int rectPosY = windowHeight - rectHeight; // keep the rectangle on the ground in the window
    int rectPosx = windowWidth / 2; // put it in the middle of the game window
    Color rectColor = RED;

    // game variables
    int velocity{0};


    SetTargetFPS(fps);
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic begins
        DrawRectangle(rectPosx, rectPosY, rectWidth, rectHeight,rectColor);
        rectPosY += velocity;

        if (IsKeyPressed(KEY_SPACE))
        {
            // make the rectangle jump
            velocity = -10;
        }
        

        // game logic ends
        EndDrawing();
    }

    CloseWindow();
}