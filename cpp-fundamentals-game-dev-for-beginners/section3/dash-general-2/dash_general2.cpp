
#include "raylib.h"

struct AnimationData
{
    Texture2D texture;
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float runningTime;
    float updateTime;
    int velocity;
};

void updateScruffyAnimation(AnimationData &scruffy);
void updateNebulaAnimation(AnimationData &nebula);

int main()
{
    // window coordinates
    const int windowDimensions[2] = {512, 380}; // width, height
    int fps = 60;
    // initialise window
    InitWindow(windowDimensions[0], windowDimensions[1], "dasher");

    // game variables
    const int gravity = 1000; // pixel per second per second
    // is the axe in air?
    bool isInAir(false);
    const int jumpVelocity = -600; // pixel per second

    // scruffy variables

    AnimationData scruffyData{
        .texture = LoadTexture("./textures/scarfy.png"),
        .rectangle = {0.0, 0.0, scruffyData.texture.width / 6.0, scruffyData.texture.height},
        .position = {windowDimensions[0] / 2 - scruffyData.rectangle.width / 2, windowDimensions[1] - scruffyData.rectangle.height}, // bottom centre
        .frame = 0,
        .runningTime = 0.0,
        .updateTime = 1.0 / 12.0,
        .velocity = 0, // px per sec
    };

    // nebula variables
    AnimationData nebulae[3]{};
    for (int i = 0; i < 3; i++)
    {
        nebulae[i].texture = LoadTexture("./textures/12_nebula_spritesheet.png");
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebulae[i].texture.width / 8;
        nebulae[i].rectangle.height = nebulae[i].texture.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].velocity = -200; // px per sec
        nebulae[i].position.y = windowDimensions[1] - nebulae[i].rectangle.height;
    }

    nebulae[0].position.x = windowDimensions[0];
    nebulae[1].position.x = windowDimensions[0] + 300; // offset to the right of the screen
    nebulae[2].position.x = windowDimensions[0] + 600;

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
        if (scruffyData.position.y >= windowDimensions[1] - scruffyData.rectangle.height)
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
        for (int i = 0; i < 3; i++)
        {
            nebulae[i].position.x += nebulae[i].velocity * dT;
        }

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
        for (int i = 0; i < 3; i++)
        {
            nebulae[i].runningTime += dT;
            updateNebulaAnimation(nebulae[i]);
        }

        // draw scruffy rect
        DrawTextureRec(scruffyData.texture, scruffyData.rectangle, scruffyData.position, WHITE);
        // draw nebula rect
        DrawTextureRec(nebulae[1].texture, nebulae[1].rectangle, nebulae[1].position, WHITE);
        DrawTextureRec(nebulae[2].texture, nebulae[2].rectangle, nebulae[2].position, RED);
        DrawTextureRec(nebulae[0].texture, nebulae[0].rectangle, nebulae[0].position, GREEN);

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffyData.texture);
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(nebulae[i].texture);
    }

    CloseWindow();
}

void updateScruffyAnimation(AnimationData &scruffy)
{
    if (scruffy.runningTime >= scruffy.updateTime)
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

void updateNebulaAnimation(AnimationData &nebula)
{
    if (nebula.runningTime >= nebula.updateTime)
    {
        nebula.runningTime = 0.0;
        // update scruffy animation frame
        nebula.rectangle.x = nebula.frame * nebula.rectangle.width;
        nebula.frame++;

        if (nebula.frame > 7) // 8 x 8 sheet and we only use the 1st row
        {
            // this check is necessary as we only have 0 to 5 sheets in the sprite sheet
            nebula.frame = 0;
        }
    }
}