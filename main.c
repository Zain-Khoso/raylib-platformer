#include "raylib.h"

int main(void)
{
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    InitWindow(screen_width, screen_height, "Palm Tree Island");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
