#include "string.h"
#include "raylib.h"

// General
#define TITLE "Palm Tree Island"
#define FPS 60
#define GRAVITY 1

// Player
#define PLAYER_SPEED 12
#define PLAYER_JUMP_POWER 20

// Player Structure
typedef struct Player
{
    Vector2 position;
    int velocity;
} Player;

int main(void)
{
    // Window setup
    InitWindow(0, 0, TITLE);

    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    SetWindowSize(screen_width, screen_height);

    // Loading player
    Player player = {0};
    player.velocity = 0;
    // Redering
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        if (IsKeyPressed(KEY_SPACE))
        {
            player.velocity = -PLAYER_JUMP_POWER;
        }

        // Player
        player.velocity += GRAVITY;
        player.position.y += player.velocity;

        DrawRectangle(player.position.x, player.position.y, TILE_SIZE / 2, TILE_SIZE, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
