
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
    int velocity{0};  // pixel per frame
    const int gravity = 1; // pixel per frame per frame


    SetTargetFPS(fps);
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic begins

        /**
         * the sign is + as the (0,0) coordinate corresponds to the top left corner of the window
        */
        // ground check and update velocity
        if (rectPosY >= windowHeight - rectHeight)
        {
            // rectangle is in the ground
            velocity = 0;
            
        } else {

            // rectangle is in the air
            velocity += gravity; 
        }
        
        if (IsKeyPressed(KEY_SPACE))
        {
            // make the rectangle jump
            velocity -= 10; // negative sign means upwards
        }
        

        // update position
        rectPosY += velocity;
        
        // draw rect
        DrawRectangle(rectPosx, rectPosY, rectWidth, rectHeight,rectColor);

        

        // game logic ends
        EndDrawing();
    }

    CloseWindow();
}