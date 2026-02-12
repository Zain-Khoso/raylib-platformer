#include "string.h"
#include "raylib.h"

#define TILE_SIZE 64
#define TILE_AMOUNT 1000

int main(void)
{
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    InitWindow(screen_width, screen_height, "Palm Tree Island");

    Rectangle player = {0};
    Rectangle tiles[TILE_AMOUNT] = {0};

    char *level_map[] = {
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "XX                                    XX",
        "XX                                    XX",
        "XX                                    XX",
        "XX  P                                 XX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    };
    int level_rows = sizeof(level_map) / sizeof(level_map[0]);
    int level_cols = strlen(level_map[0]);

    for (int row = 0; row < level_rows; row++)
    {
        for (int col = 0; col < level_cols; col++)
        {
            int x_pos = col * TILE_SIZE;
            int y_pos = row * TILE_SIZE;

            if (level_map[row][col] == 'X')
            {
                Rectangle tile = {0};

                tile.width = TILE_SIZE;
                tile.height = TILE_SIZE;
                tile.x = x_pos;
                tile.y = y_pos;
                tiles[(row * level_cols) + col] = tile;
            }

            else if (level_map[row][col] == 'P')
            {
                player.width = TILE_SIZE / 2;
                player.height = TILE_SIZE;
                player.x = x_pos;
                player.y = y_pos;
            }
        }
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        for (int i = 0; i < TILE_AMOUNT; i++)
            DrawRectangleRec(tiles[i], LIGHTGRAY);

        DrawRectangleRec(player, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
