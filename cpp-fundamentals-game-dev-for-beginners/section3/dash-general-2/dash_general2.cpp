
#include "raylib.h"

// update animation 12 times in 1 sec
const float SCRUFFY_UPDATE_TIME = 1.0 / 12.0;
const float NEBULA_UPDATE_TIME = 1.0 / 12.0;

struct AnimationData
{
    Texture2D texture;
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float runningTime;
    int velocity;
};

void updateScruffyAnimation(AnimationData &scruffy);
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
    const int gravity = 1000; // pixel per second per second
    // is the axe in air?
    bool isInAir(false);
    const int jumpVelocity = -600; // pixel per second

    // scruffy variables

    AnimationData scruffyData{
        .texture = LoadTexture("./textures/scarfy.png"),
        .rectangle = {0.0, 0.0, scruffyData.texture.width / 6.0, scruffyData.texture.height},
        .position = {windowWidth / 2 - scruffyData.rectangle.width / 2, windowHeight - scruffyData.rectangle.height}, // bottom centre
        .frame = 0,
        .runningTime = 0.0,
        .velocity = 0, // px per sec
    };

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
        if (scruffyData.position.y >= windowHeight - scruffyData.rectangle.height)
        {
            // rectangle is in the ground
            scruffyData.velocity = 0;
            isInAir = false;
        }
        else
        {

            // rectangle is in the air
            scruffyData.velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            // make the rectangle jump
            scruffyData.velocity += jumpVelocity;
        }

        // update
        nebulaPosition.x += nebulaVelocity * dT;

        // update scruffy position
        scruffyData.position.y += scruffyData.velocity * dT;

        // scruffy animation logic
        if (!isInAir) // stop animating when in air
        {
            // update running time
            scruffyData.runningTime += dT;
            updateScruffyAnimation(scruffyData);
        }

        // nebula animation logic
        nebulaRunningTime += dT;
        updateHazardAnimation(nebulaRunningTime, nebulaFrame, nebulaRecangle);

        // draw scruffy rect
        DrawTextureRec(scruffyData.texture, scruffyData.rectangle, scruffyData.position, WHITE);
        // draw nebula rect
        DrawTextureRec(nebula, nebulaRecangle, nebulaPosition, WHITE);

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffyData.texture);
    UnloadTexture(nebula);
    CloseWindow();
}

void updateScruffyAnimation(AnimationData &scruffy)
{
    if (scruffy.runningTime >= SCRUFFY_UPDATE_TIME)
    {
        scruffy.runningTime = 0.0;
        // update scruffy animation frame
        scruffy.rectangle.x = scruffy.frame * scruffy.rectangle.width;
        scruffy.frame++;

        if (scruffy.frame > 5)
        {
            // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
            scruffy.frame = 0;
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

        if (frame > 7) // 8 x 8 sheet and we only use the 1st row
        {
            // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
            frame = 0;
        }
    }
}