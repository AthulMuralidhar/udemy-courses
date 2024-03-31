
#include "raylib.h"

int main() {
    // window coordinates
    const int windowWidth = 512;
    const int windowHeight = 380;
    int fps = 60;
    // initialise window
    InitWindow(windowWidth, windowHeight, "dasher");

    // game variablescruffyPos.x = windowWidth/2 - scruffyRec.width / 2;
    int velocity{0};  // pixel per frame
    const int gravity = 1; // pixel per frame per frame
    // is the axe in air?
    bool isInAir(false);
    const int jumpVelocity = -22;


    // scruffy
    Texture2D scruffy = LoadTexture("./textures/scarfy.png");
    Rectangle scruffyRec;
    scruffyRec.width = scruffy.width / 6; // 6 cause there are 6 pictures in the sprite sheet
    scruffyRec.height = scruffy.height;
    scruffyRec.x = 0;
    scruffyRec.y = 0;
    Vector2 scruffyPos;
    // first part alighes the (0,0) of scarfy rec to the centre of the screen, but we need scruffy to be exactly in the centre of the screen so we substract the other bit
    scruffyPos.x = windowWidth/2 - scruffyRec.width / 2;
    scruffyPos.y = windowHeight - scruffyRec.height; // this places scruffy on the ground


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
        if (scruffyPos.y >= windowHeight - scruffyRec.height)
        {
            // rectangle is in the ground
            velocity = 0;
            isInAir = false;
            
        } else {

            // rectangle is in the air
            velocity += gravity; 
            isInAir = true;
        }
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            // make the rectangle jump
            velocity += jumpVelocity; // negative sign means upwards
        }
        

        // update position
        scruffyPos.y += velocity;
        
        // draw rect
        DrawTextureRec(scruffy,scruffyRec,scruffyPos, WHITE);
        

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffy);
    CloseWindow();
}