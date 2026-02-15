#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// General
#define TITLE "Palm Tree Island"
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define FPS 60
#define GRAVITY 1

// Terrain
#define TILE_SIZE 64

typedef struct TileNode
{
    Rectangle rect;
    Color color;
    struct TileNode *next;
} TileNode;

const char *level_map[] = {
    "                                                                                    ",
    "                                                                                    ",
    "                                                                                    ",
    " XX    XXX            XX     XX    XXX            XX     XX    XXX            XX    ",
    " XX                          XX                          XX                         ",
    " XXXX         XX         XX  XXXX         XX         XX  XXXX         XX         XX ",
    " XXXX  P    XX               XXXX       XX               XXXX       XX              ",
    " XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX    ",
    "       X  XXXX    XX  XXX          X  XXXX    XX  XXX          X  XXXX    XX  XXX   ",
    "    XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX  ",
    "XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  ",
};

// Player
#define PLAYER_SPEED 12
#define PLAYER_JUMP_POWER 20

// Player Structure
typedef struct Player
{
    Vector2 velocity;
    Rectangle rect;
    Color color;
} Player;

// Function Prototypes
void create_sprites(TileNode **list_ptr, Player *player);
void player_movement(Player *player);

int main(void)
{
    // Window setup
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    ToggleFullscreen();

    // Loading player
    Player player = {
        .rect = {
            .width = TILE_SIZE / 2,
            .height = TILE_SIZE,
            .x = 0,
            .y = 0,
        },
        .velocity = {
            .x = 0,
            .y = 0,
        },
        .color = BLUE,
    };

    // Loading terrain
    TileNode *tile_ptr = NULL;

    create_sprites(&tile_ptr, &player);

    // Redering
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        player_movement(&player);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Terrain
        for (TileNode *ptr = tile_ptr; ptr != NULL; ptr = ptr->next)
        {
            // Collissions
            bool is_colliding = CheckCollisionRecs(player.rect, ptr->rect);

            if (is_colliding)
            {
                int player_width = player.rect.width;
                int player_height = player.rect.height;

                int player_top = player.rect.y;
                int player_bottom = player.rect.y + player_height;
                int player_left = player.rect.x;
                int player_right = player.rect.x + player_width;

                int tile_top = ptr->rect.y;
                int tile_bottom = ptr->rect.y + TILE_SIZE;
                int tile_left = ptr->rect.x;
                int tile_right = ptr->rect.x + TILE_SIZE;

                bool jumping = player.velocity.y < 0;
                bool moving_left = player.velocity.x < 0;
                bool moving_right = player.velocity.x > 0;

                if (jumping && (player_top < tile_bottom))
                {
                    player.rect.y = tile_bottom;
                }

                if (!jumping && (player_bottom > tile_top))
                {
                    player.velocity.y = 0;
                    player.rect.y = tile_top - player_height;
                }

                if (moving_left && (player_left < tile_right))
                {
                    player.rect.x = tile_right;
                }

                if (moving_right && (player_right > tile_left))
                {
                    player.rect.x = tile_left - player_width;
                }
            }

            // Rendering
            DrawRectangleRec(ptr->rect, ptr->color);
        }

        // Player
        DrawRectangleRec(player.rect, player.color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void create_sprites(TileNode **list_ptr, Player *player)
{
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
                // Allocating memory for a new node
                TileNode *new_node = malloc(sizeof(TileNode));

                // Setting up the new node
                new_node->rect = (Rectangle){
                    .width = TILE_SIZE,
                    .height = TILE_SIZE,
                    .x = x_pos,
                    .y = y_pos,
                };
                new_node->color = LIGHTGRAY;

                // Prepending this new tile node to the given linked list
                new_node->next = *list_ptr;
                *list_ptr = new_node;
            }

            else if (level_map[row][col] == 'P')
            {
                player->rect.x = x_pos;
                player->rect.y = y_pos;
            }

            else
            {
                continue;
            }
        }
    }
}

void player_movement(Player *player)
{
    bool jumping = player->velocity.y < 0;

    if (!jumping && IsKeyPressed(KEY_SPACE))
    {
        player->velocity.y = -PLAYER_JUMP_POWER;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        player->velocity.x = -PLAYER_SPEED;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        player->velocity.x = PLAYER_SPEED;
    }
    else
    {
        player->velocity.x = 0;
    }

    player->velocity.y += GRAVITY;

    player->rect.y += player->velocity.y;
    player->rect.x += player->velocity.x;
}