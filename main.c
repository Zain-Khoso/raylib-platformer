#include "string.h"
#include "raylib.h"

#define GRAVITY 4

#define TILE_SIZE 64
#define TILE_AMOUNT 1000

#define PLAYER_SPEED 12
#define PLAYER_JUMP_POWER 60

typedef struct Player
{
    Vector2 position;
    int velocity
} Player;

int main(void)
{
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    InitWindow(screen_width, screen_height, "Palm Tree Island");

    Player player = {0};
    player.velocity = 0;

    Rectangle tiles[TILE_AMOUNT] = {0};

    // char *level_map[] = {
    //     "    P                                                                               ",
    //     "                                                                                    ",
    //     "                                                                                    ",
    //     " XX    XXX            XX     XX    XXX            XX     XX    XXX            XX    ",
    //     " XX                          XX                          XX                         ",
    //     " XXXX         XX         XX  XXXX         XX         XX  XXXX         XX         XX ",
    //     " XXXX       XX               XXXX       XX               XXXX       XX              ",
    //     " XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX    ",
    //     "       X  XXXX    XX  XXX          X  XXXX    XX  XXX          X  XXXX    XX  XXX   ",
    //     "    XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX  ",
    //     "XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  ",
    // };

    char *level_map[] = {
        "  P                                                                                 ",
        "                                                                                    ",
        "                                                                                    ",
        "                                                                                    ",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
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
                player.position.x = x_pos;
                player.position.y = y_pos;
            }
        }
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        for (int i = 0; i < TILE_AMOUNT; i++)
        {
            DrawRectangleRec(tiles[i], LIGHTGRAY);
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            player.velocity = -PLAYER_JUMP_POWER;
        }

        player.velocity += GRAVITY;
        player.position.y += player.velocity;

        DrawRectangle(player.position.x, player.position.y, TILE_SIZE / 2, TILE_SIZE, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
