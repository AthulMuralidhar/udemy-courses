
#include "raylib.h"

int main()
{
    // window coordinates
    const int windowWidth = 512;
    const int windowHeight = 380;
    int fps = 60;
    // initialise window
    InitWindow(windowWidth, windowHeight, "dasher");

    // game variables
    int velocity{0};          // pixel per second
    const int gravity = 1000; // pixel per second per second
    // is the axe in air?
    bool isInAir(false);
    const int jumpVelocity = -600; // pixel per second

    // animation frame
    int frame{};
    // time between each animation frame
    // also this number 12.0 is a choice based on the sprite sheet and the time between animations
    // can vary if there are more sheets in the sprite and how fast we have set the fps
    // for ex: using 24.0 just means that the animation now runs twice as fast
    const float updateTime = 1.0 / 12.0; // we want to update animation 12 times in 1 sec
    // time passed between 2 animation frames
    float runningTime{};

    // scruffy
    Texture2D scruffy = LoadTexture("./textures/scarfy.png");
    Rectangle scruffyRec;
    scruffyRec.width = scruffy.width / 6; // 6 cause there are 6 pictures in the sprite sheet
    scruffyRec.height = scruffy.height;
    scruffyRec.x = 0;
    scruffyRec.y = 0;
    Vector2 scruffyPos;
    // first part aligns`   es the (0,0) of scarfy rec to the centre of the screen, but we need scruffy to be exactly in the centre of the screen so we substract the other bit
    scruffyPos.x = windowWidth / 2 - scruffyRec.width / 2;
    scruffyPos.y = windowHeight - scruffyRec.height; // this places scruffy on the ground

    SetTargetFPS(fps);
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time - time since last frame
        const float dT = GetFrameTime();

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
        }
        else
        {

            // rectangle is in the air
            // velocity = velocity*dT + gravity;
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            // make the rectangle jump
            // velocity = (velocity + jumpVelocity)*dT; // negative sign means upwards
            velocity += jumpVelocity; // negative sign means upwards
        }

        // update position
        scruffyPos.y += velocity * dT;

        // animation logic
        // update running time
        runningTime += dT;

        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            // update animation frame
            scruffyRec.x = frame * scruffyRec.width;
            frame++;
            if (frame > 5)
            {
                // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
                frame = 0;
            }
        }

        // draw rect
        DrawTextureRec(scruffy, scruffyRec, scruffyPos, WHITE);

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffy);
    CloseWindow();
}