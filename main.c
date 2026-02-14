#include "string.h"
#include "raylib.h"

#define TITLE "Palm Tree Island"
#define FPS 60

int main(void)
{
    // Window setup
    InitWindow(0, 0, TITLE);

    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    SetWindowSize(screen_width, screen_height);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
