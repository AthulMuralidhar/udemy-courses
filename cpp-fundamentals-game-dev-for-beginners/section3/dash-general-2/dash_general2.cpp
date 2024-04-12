
#include "raylib.h"

// update animation 12 times in 1 sec
const float SCRUFFY_UPDATE_TIME = 1.0 / 12.0;
const float NEBULA_UPDATE_TIME = 1.0 / 12.0;

void updateScruffyAnimation(float &runningTime, int &frame, Rectangle &scruffyRectangle);

void updateHazardAnimation(float &runningTime, int &frame, Rectangle &nebulaRectangle);

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



    // scruffy variables
    Texture2D scruffy = LoadTexture("./textures/scarfy.png");
    Rectangle scruffyRectangle{0.0, 0.0, scruffy.width / 6.0, scruffy.height};
    Vector2 scruffyPosition{windowWidth / 2 - scruffyRectangle.width / 2, windowHeight - scruffyRectangle.height}; // bottom centre
    // animation frame
    int scruffyFrame{};
    // time passed between 2 animation frames
    float scruffyRunningTime{};

    // nebula variables
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
    Rectangle nebulaRecangle{0.0, 0.0, nebula.width / 8, nebula.height / 8}; // 8 x 8 sprite sheet
    Vector2 nebulaPosition{windowWidth, windowHeight - nebulaRecangle.height};
    // nebula x velocity (pixels/second)
    int nebulaVelocity{-200};
    int nebulaFrame{};
    float nebulaRunningTime{};   


    SetTargetFPS(fps);
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time - time since last frame
        const float dT = GetFrameTime();

        // game logic begins
        // ground check and update velocity
        if (scruffyPosition.y >= windowHeight - scruffyRectangle.height)
        {
            // rectangle is in the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {

            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            // make the rectangle jump
            velocity += jumpVelocity;
        }

        // update
        nebulaPosition.x += nebulaVelocity * dT;

        // update scruffy position
        scruffyPosition.y += velocity * dT;

        // scruffy animation logic
        if (!isInAir) // stop animating when in air
        {
            // update running time
            scruffyRunningTime += dT;
            updateScruffyAnimation(scruffyRunningTime, scruffyFrame, scruffyRectangle);
        }

        // nebula animation logic
        nebulaRunningTime += dT;
        updateHazardAnimation(nebulaRunningTime, nebulaFrame, nebulaRecangle);

        // draw scruffy rect
        DrawTextureRec(scruffy, scruffyRectangle, scruffyPosition, WHITE);
        // draw nebula rect
        DrawTextureRec(nebula, nebulaRecangle, nebulaPosition, WHITE);

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffy);
    UnloadTexture(nebula);
    CloseWindow();
}

void updateScruffyAnimation(float &runningTime, int &frame, Rectangle &scruffyRectangle)
{
    if (runningTime >= SCRUFFY_UPDATE_TIME)
    {
        runningTime = 0.0;
        // update scruffy animation frame
        scruffyRectangle.x = frame * scruffyRectangle.width;
        frame++;

        if (frame > 5)
        {
            // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
            frame = 0;
        }
    }
}


void updateHazardAnimation(float &runningTime, int &frame, Rectangle &nebulaRectangle)
{
    if (runningTime >= NEBULA_UPDATE_TIME)
    {
        runningTime = 0.0;
        // update scruffy animation frame
        nebulaRectangle.x = frame * nebulaRectangle.width;
        frame++;

        if (frame > 7)  // 8 x 8 sheet and we only use the 1st row
        {
            // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
            frame = 0;
        }
    }
}