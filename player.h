#ifndef PLAYER_H

#define PLAYER_H
#define PLAYER_FRAME_SPEED 0.15f

#include "shared.h"
#include "tiles.h"

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

Player create_player();
void animate_player(Player *player);
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);

Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

#endif
