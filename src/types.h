#pragma once

// Header files
#include <math.h>
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
    unsigned int error;
    unsigned int lines;
    char **data;
} FileRead;

typedef struct
{
    unsigned int error;
    unsigned int rows;
    char ***data;
} CSVRead;

typedef struct TextureStore
{
    char *type;
    char *name;
    unsigned int total_frames;
    bool repeat;
    Texture2D *frames;
} TextureStore;

typedef struct TileNode
{
    Rectangle rect;
    Color color;
    struct TileNode *next;
} TileNode;

enum PlayerStatus
{
    IDLE, // = 0
    RUN,  // = 1
    HIT,  // = 2
    JUMP, // = 3
    FALL, // = 4
    LAND, // = 5
};

typedef struct Player
{
    float speed;
    float gravity;
    float jump_power;
    float frame_speed;
    float current_frame;
    enum PlayerStatus status;
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
