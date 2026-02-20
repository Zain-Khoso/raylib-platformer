#pragma once

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <stdbool.h>

// Statically defined values
#define TITLE "Palm Tree Island"
#define FPS 60

#define MORE_LINES 1024
#define MORE_CHARS 1024

#define TILE_SIZE 32

extern const char *level_map[];

// Custom data structures
typedef struct
{
    unsigned int erorr;
    unsigned int lines;
    char **data;
} FileRead;

typedef struct
{
    unsigned int erorr;
    unsigned int rows;
    char ***data;
} CSVRead;

typedef struct TextureStore
{
    char *type;
    char *name;
    unsigned int total_frames;
    Texture2D *frames;
} TextureStore;

typedef struct TileNode
{
    Rectangle rect;
    Color color;
    struct TileNode *next;
} TileNode;

typedef struct Player
{
    float speed;
    float gravity;
    float jump_power;
    float frame_speed;
    float current_frame;
    char *status;
    Color tint;

    bool on_ground;
    bool facing_right;

    Rectangle rect;
    Vector2 velocity;

    TextureStore *textures;
    Rectangle texture_rect;
    Rectangle texture_cut;
    Vector2 texture_org;
    Texture2D texture;
} Player;

// File reader prototypes
FileRead *load_file(const char *path);
void unload_file(FileRead *file);

CSVRead *read_csv(const FileRead *file);
void forget_csv(CSVRead *csv);

// Asset manager prototypes
TextureStore *load_textures();
void unload_textures(TextureStore *texture_store);
TextureStore *get_textures(TextureStore *texture_store, const char *query);

// Player prototypes
Player *create_player(TextureStore *texture_store);
void delete_player(Player *player);
void animate_player(TextureStore *texture_store, Player *player);
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);
TextureStore *get_animation(TextureStore *texture_store, Player *player);

// Camera prototypes
Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

// Sprite prototypes
TileNode *create_sprites(struct Player *player);
void delete_sprites(TileNode **list_ptr);
