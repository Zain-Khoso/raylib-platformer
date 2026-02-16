#ifndef PLAYER_H

#define PLAYER_H

#include "shared.h"
#include "tiles.h"

typedef struct Player
{
    Vector2 velocity;
    Rectangle rect;
    Color color;
    bool on_ground;
} Player;

Player create_player();
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);

Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

#endif
