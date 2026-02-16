#include <string.h>

#include "player.h"

// Function to initial create the player
Player create_player()
{
    return (Player){
        .rect = {0, 0, TILE_SIZE / 2, TILE_SIZE},
        .velocity = {0, 0},
        .color = BLUE,
        .on_ground = false};
}

// Function to handle player's horizontal movements and horizontal collisions
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr)
{
    if (IsKeyDown(KEY_LEFT))
        player->velocity.x = -PLAYER_SPEED;
    else if (IsKeyDown(KEY_RIGHT))
        player->velocity.x = PLAYER_SPEED;
    else
        player->velocity.x = 0;

    player->rect.x += player->velocity.x;

    for (TileNode *tile = list_ptr; tile != NULL; tile = tile->next)
    {
        if (CheckCollisionRecs(player->rect, tile->rect))
        {
            if (player->velocity.x < 0)
                player->rect.x = tile->rect.x + tile->rect.width;
            else if (player->velocity.x > 0)
                player->rect.x = tile->rect.x - player->rect.width;
        }
    }
}

// Function to handle player's vertical movements and vertical collisions
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

// Function to initially create a camera
Camera2D create_camera(Player *player)
{
    return (Camera2D){
        .target = {player->rect.x, player->rect.y},
        .offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .rotation = 0.0f,
        .zoom = 1.0f};
}

// Function to handle camera movement
void update_camera(Camera2D *camera, Player *player)
{
    int map_width = strlen(level_map[0]) * TILE_SIZE;
    int map_height = 11 * TILE_SIZE;
    float delta = GetFrameTime();
    float lerp_speed = 3.0f;

    camera->target.x += (player->rect.x - camera->target.x) * lerp_speed * delta;
    camera->target.y += (player->rect.y - camera->target.y) * lerp_speed * delta;

    if (camera->target.x < camera->offset.x)
        camera->target.x = camera->offset.x;
    if (camera->target.x > map_width - camera->offset.x)
        camera->target.x = map_width - camera->offset.x;
    if (camera->target.y > map_height - camera->offset.y)
        camera->target.y = map_height - camera->offset.y;
}
