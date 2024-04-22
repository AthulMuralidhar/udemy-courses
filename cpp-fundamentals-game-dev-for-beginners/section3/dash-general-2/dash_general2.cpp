
#include "raylib.h"
#include <iostream>

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
    bool collision{};

    // textures
    const Texture2D scruffyTexture = LoadTexture("./textures/scarfy.png");
    const Texture2D nebulaTexture = LoadTexture("./textures/12_nebula_spritesheet.png");
    const Texture2D backgroundTexture = LoadTexture("./textures/far-buildings.png");
    const Texture2D midgroundTexture = LoadTexture("./textures/back-buildings.png");
    const Texture2D foregroundTexture = LoadTexture("./textures/foreground.png");

    // scrolling variables
    float bgX{};
    float mgX{};
    float fgX{};
    Vector2 bg1Position{};
    Vector2 bg2Position{};
    Vector2 mg1Position{};
    Vector2 mg2Position{};
    Vector2 fg1Position{};
    Vector2 fg2Position{};

    // scruffy variables
    AnimationData scruffyData{
        .texture = scruffyTexture,
        .rectangle = {0.0, 0.0, scruffyTexture.width / 6.0, scruffyTexture.height},
        .position = {windowDimensions[0] / 2 - scruffyData.rectangle.width / 2, windowDimensions[1] - scruffyData.rectangle.height}, // bottom centre
        .frame = 0,
        .runningTime = 0.0,
        .updateTime = 1.0 / 12.0,
        .velocity = 0, // px per sec
    };

    // nebula variables
    const int numberOfNebulae = 6;
    int nebulaVelocity{-200}; // px per sec
    AnimationData nebulae[numberOfNebulae]{};
    for (int i = 0; i < numberOfNebulae; i++)
    {
        nebulae[i].texture = nebulaTexture;
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebulaTexture.width / 8;
        nebulae[i].rectangle.height = nebulaTexture.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].velocity = nebulaVelocity;
        nebulae[i].position.y = windowDimensions[1] - nebulae[i].rectangle.height;
        nebulae[i].position.x = windowDimensions[0] + (300 * i); // offset to the right of the screen
    }

    // finish line
    float finishLine{nebulae[numberOfNebulae - 1].position.x};

    SetTargetFPS(fps);
    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // delta time - time since last frame
        const float dT = GetFrameTime();

        // scroll background
        bgX -= 20 * dT;
        if (bgX <= -backgroundTexture.width * 2) // this check ensures that the bg position is reset once the scroll passes the screen
        {
            bgX = 0.0;
        }

        // scroll migground
        mgX -= 40 * dT;
        if (mgX <= -midgroundTexture.width * 2)
        {
            mgX = 0.0;
        }

        // scroll foreground
        fgX -= 80 * dT;
        if (fgX <= -foregroundTexture.width * 2)
        {
            fgX = 0.0;
        }

        // draw background
        bg1Position.x = bgX;
        bg1Position.y = 0.0;
        bg2Position.x = bgX + backgroundTexture.width * 2;
        bg2Position.y = 0.0;

        DrawTextureEx(backgroundTexture, bg1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(backgroundTexture, bg2Position, 0.0, 2.0, WHITE);
        // draw midground
        mg1Position.x = mgX;
        mg1Position.y = 0.0;
        mg2Position.x = mgX + midgroundTexture.width * 2;
        mg2Position.y = 0.0;

        DrawTextureEx(midgroundTexture, mg1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(midgroundTexture, mg2Position, 0.0, 2.0, WHITE);

        // draw foreground
        fg1Position.x = fgX;
        fg1Position.y = 0.0;
        fg2Position.x = fgX + foregroundTexture.width * 2;
        fg2Position.y = 0.0;

        DrawTextureEx(foregroundTexture, fg1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(foregroundTexture, fg2Position, 0.0, 2.0, WHITE);

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

        // update nebula
        for (int i = 0; i < numberOfNebulae; i++)
        {
            nebulae[i].position.x += nebulae[i].velocity * dT;
        }
        // update finish line
        finishLine += nebulaVelocity * dT;
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
        for (int i = 0; i < numberOfNebulae; i++)
        {
            nebulae[i].runningTime += dT;
            updateNebulaAnimation(nebulae[i]);
        }

        for (AnimationData nebula : nebulae)
        {
            float nebulaPadding = 50.0;
            Rectangle nebRec{
                .x = nebula.position.x + nebulaPadding,
                .y = nebula.position.y + nebulaPadding,
                .width = nebula.rectangle.width - 2 * nebulaPadding,
                .height = nebula.rectangle.height - 2 * nebulaPadding,
            };

            Rectangle scruffyRec{
                .x = scruffyData.position.x,
                .y = scruffyData.position.y,
                .width = scruffyData.rectangle.width,
                .height = scruffyData.rectangle.height,
            };

            if (CheckCollisionRecs(nebRec, scruffyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            // loose the game
            DrawText("game over!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else if (scruffyData.position.x >= finishLine)
        {

            DrawText("you won!", windowDimensions[0] / 4, windowDimensions[1] / 2, 40, RED);
        }
        else
        {
            // draw scruffy rect
            DrawTextureRec(scruffyTexture, scruffyData.rectangle, scruffyData.position, WHITE);
            // draw nebula rect
            for (int i = 0; i < numberOfNebulae; i++)
            {
                DrawTextureRec(nebulaTexture, nebulae[i].rectangle, nebulae[i].position, WHITE);
            }
        }

        std::cout << collision << std::endl;

        // game logic ends
        EndDrawing();
    }

    UnloadTexture(scruffyTexture);
    UnloadTexture(nebulaTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(midgroundTexture);
    UnloadTexture(foregroundTexture);

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