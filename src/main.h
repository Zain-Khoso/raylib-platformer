#pragma once

// Header files
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// Statically defined values
#define TITLE "Palm Tree Island"
#define FPS 60

#define TILE_SIZE 64

#define GRAVITY 32.0f
#define PLAYER_SPEED 256.0f
#define PLAYER_JUMP_POWER 512.0f
#define PLAYER_FRAME_SPEED 0.15f

extern const char *level_map[];

// Custom data structures
typedef struct TileNode
{
    Rectangle rect;
    Color color;
    struct TileNode *next;
} TileNode;

typedef struct Player
{
    Vector2 velocity;
    Vector2 texture_pos;
    Rectangle rect;
    Color color;

    Texture2D texture;
    Texture2D textures[5];

    bool on_ground;
    float frame;
} Player;

// Player prototypes
Player create_player();
void animate_player(Player *player);
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);

// Camera prototypes
Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

// Sprite prototypes
TileNode *create_sprites(struct Player *player);
void delete_sprites(TileNode **list_ptr);
