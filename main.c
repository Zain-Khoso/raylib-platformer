#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// General
#define TITLE "Palm Tree Island"
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
    bool on_ground;
} Player;

// Function Prototypes
TileNode *create_sprites(Player *player);
void delete_sprites(TileNode **list_ptr);

Player create_player();
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);

Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

int main(void)
{
    // Window setup
    InitWindow(GetScreenWidth(), GetScreenHeight(), TITLE);

    ToggleFullscreen();

    // Loading player
    Player player = create_player();

    // Loading terrain
    TileNode *tile_ptr = create_sprites(&player);

    // Camera setup
    Camera2D camera = create_camera(&player);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Physics
        player_horizontal_movement_collision(&player, tile_ptr);
        player_vertical_movement_collision(&player, tile_ptr);

        update_camera(&camera, &player);

        // Rendering
        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode2D(camera);

        // Terrain
        for (TileNode *ptr = tile_ptr; ptr != NULL; ptr = ptr->next)
        {
            DrawRectangleRec(ptr->rect, ptr->color);
        }

        // Player
        DrawRectangleRec(player.rect, player.color);

        EndMode2D();

        EndDrawing();
    }

    delete_sprites(&tile_ptr);

    CloseWindow();

    return 0;
}

TileNode *create_sprites(Player *player)
{
    TileNode *list_ptr = NULL;

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
                new_node->next = list_ptr;
                list_ptr = new_node;
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

    return list_ptr;
}

void delete_sprites(TileNode **list_ptr)
{
    TileNode *current = *list_ptr;

    while (current != NULL)
    {
        TileNode *next_node = current->next;

        free(current);

        current = next_node;
    }

    *list_ptr = NULL;
}

Player create_player()
{
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
        .on_ground = false,
    };

    return player;
}

void player_horizontal_movement_collision(Player *player, TileNode *list_ptr)
{
    // Movement
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

    player->rect.x += player->velocity.x;

    // Collisions
    for (TileNode *tile = list_ptr; tile != NULL; tile = tile->next)
    {
        if (CheckCollisionRecs(player->rect, tile->rect))
        {
            if (player->velocity.x < 0)
            {
                player->rect.x = tile->rect.x + tile->rect.width;
            }

            else if (player->velocity.x > 0)
            {
                player->rect.x = tile->rect.x - player->rect.width;
            }
        }
    }
}

void player_vertical_movement_collision(Player *player, TileNode *list_ptr)
{
    if (player->on_ground && IsKeyPressed(KEY_SPACE))
    {
        player->velocity.y = -PLAYER_JUMP_POWER;
        player->on_ground = false;
    }

    player->velocity.y += GRAVITY;
    player->rect.y += player->velocity.y;
    player->on_ground = false;

    // Collisions
    for (TileNode *tile = list_ptr; tile != NULL; tile = tile->next)
    {
        if (CheckCollisionRecs(player->rect, tile->rect))
        {
            if (player->velocity.y > 0)
            {
                player->velocity.y = 0;
                player->on_ground = true;
                player->rect.y = tile->rect.y - player->rect.height;
            }
            else if (player->velocity.y < 0)
            {
                player->rect.y = tile->rect.y + tile->rect.width;
                player->velocity.y = 0;
            }
        }
    }
}

Camera2D create_camera(Player *player)
{
    Camera2D camera = {
        .target = {
            .x = player->rect.x,
            .y = player->rect.y,
        },
        .offset = {
            .x = GetScreenWidth() / 2.0f,
            .y = GetScreenHeight() / 2.0f,
        },
        .rotation = 0.0f,
        .zoom = 1.0f,
    };

    return camera;
}

void update_camera(Camera2D *camera, Player *player)
{
    int rows_num = (sizeof(level_map) / sizeof(level_map[0]));

    // Target
    camera->target.x = player->rect.x;
    camera->target.y = player->rect.y;

    // Offset
    camera->offset.x = GetScreenWidth() / 3;
    camera->offset.y = (GetScreenHeight() - (rows_num * TILE_SIZE)) + player->rect.y;
}