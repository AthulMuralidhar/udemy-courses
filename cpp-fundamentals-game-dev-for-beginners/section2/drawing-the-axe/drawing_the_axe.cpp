
#include "raylib.h"

int main()
{

    // window coordinates
    int window_width = 800;
    int window_height = 450;
    int fps = 60;
    InitWindow(window_width, window_height, "test");

    // circle coordinates
    int circle_x = window_width / 2;
    int circle_y = window_height / 2;
    int circle_radius = 10;
    int circle_right_edge = circle_x + circle_radius;
    int circle_left_edge = circle_x - circle_radius;
    int circle_bottom_edge = circle_y + circle_radius;
    int circle_top_edge = circle_y - circle_radius;
    Color circle_color = BLUE;

    // rectangle (axe) coordinates
    int axe_x = 300;
    int axe_y = 0;
    int axe_width = 50;
    int axe_height = 50;
    int axe_bottom_edge = axe_y + axe_height;
    int axe_right_edge = axe_x + axe_width;
    int axe_top_edge = axe_y;
    int axe_left_edge = axe_x;
    Color axe_color = RED;

    int direction{10};
    int key_movement{10};

    SetTargetFPS(fps);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic begins
        DrawCircle(circle_x, circle_y, circle_radius, circle_color);
        DrawRectangle(axe_x, axe_y, axe_width, axe_height, axe_color);

        // move the axe
        axe_y += direction;
        if (axe_y > window_height || axe_y < 0)
        {
            direction = -direction;
        }

        if (IsKeyDown(KEY_D) && circle_x < window_width)
        {
            circle_x += key_movement;
            // no need to redraw as the while loop just continues to execute
        }

        if (IsKeyDown(KEY_A) && circle_x > 0)
        {
            circle_x -= key_movement;
        }

        if (IsKeyDown(KEY_W) && circle_y > 0)
        {
            circle_y -= key_movement;
        }

        if (IsKeyDown(KEY_S) && circle_y < window_height)
        {
            circle_y += key_movement;
        }

        // game logic ends

        EndDrawing();
    }
}
