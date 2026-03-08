#include "../types.h"
#include "../prototypes.h"

// Function to initially create a camera
Camera2D create_camera(Player *player)
{
    return (Camera2D){
        .target = {player->rect.x, player->rect.y},
        .offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .rotation = 0.0f,
        .zoom = 2.0f,
    };
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

    // if (camera->target.x < (camera->offset.x / camera->zoom))
    //     camera->target.x = (camera->offset.x / camera->zoom);

    // if (camera->target.x > map_width - (camera->offset.x / camera->zoom))
    //     camera->target.x = map_width - (camera->offset.x / camera->zoom);

    if (camera->target.y > map_height - (camera->offset.y / camera->zoom))
        camera->target.y = map_height - (camera->offset.y / camera->zoom);

    camera->target.x = roundf(camera->target.x);
    camera->target.y = roundf(camera->target.y);
}
