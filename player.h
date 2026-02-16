#ifndef PLAYER_H

#define PLAYER_H
#define PLAYER_FRAME_SPEED 0.5

#include "shared.h"
#include "tiles.h"

typedef struct PlayerTextures
{
    Texture2D death[4];
    Texture2D fall[1];
    Texture2D ground[2];
    Texture2D hit[4];
    Texture2D idle[5];
    Texture2D jump[3];
    Texture2D run[6];
} PlayerTextures;

typedef struct Player
{
    Vector2 velocity;
    Rectangle rect;

    Texture2D texture;
    PlayerTextures textures;

    char *animation;
    bool on_ground;
    int frame;
} Player;

Player create_player();
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);

Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

#endif
