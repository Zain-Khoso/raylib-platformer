#include "../main.h"

// Function to initial create the player
Player *create_player(TextureStore *texture_store)
{
    TextureStore *animation = get_textures(texture_store, "character_no_sword_idle");
    Player *player = calloc(sizeof(Player), 1);

    player->speed = 256.0f;
    player->gravity = 32.0f;
    player->jump_power = 512.0f;
    player->frame_speed = 0.15f;
    player->current_frame = 0.0f;
    player->status = "idle";
    player->tint = WHITE;

    player->on_ground = false;
    player->facing_right = true;

    player->velocity.x = 0;
    player->velocity.y = 0;

    player->textures = animation;
    player->texture = animation->frames[(int)player->current_frame];

    player->rect.width = player->texture.width;
    player->rect.height = player->texture.height;
    player->rect.x = 0;
    player->rect.y = 0;

    player->texture_rect.width = player->texture.width;
    player->texture_rect.height = player->texture.height;
    player->texture_rect.x = player->rect.x;
    player->texture_rect.y = player->rect.y;

    player->texture_cut.width = player->texture.width;
    player->texture_cut.height = player->texture.height;
    player->texture_cut.x = 0;
    player->texture_cut.y = 0;

    player->texture_org.x = 0;
    player->texture_org.y = 0;

    return player;
}

// Function to free the memory allocated to player
void delete_player(Player *player)
{
    free(player);
}

// Function to animate the player
void animate_player(TextureStore *texture_store, Player *player)
{
    player->textures = get_animation(texture_store, player);
    player->current_frame += player->frame_speed;

    if (player->current_frame > player->textures->total_frames)
    {
        player->current_frame = 0.0f;
    }

    player->texture = player->textures->frames[(int)player->current_frame];

    if (player->facing_right)
        player->texture_cut.width = player->texture.width;
    else
        player->texture_cut.width = -player->texture.width;

    player->texture_cut.height = player->texture.height;

    player->texture_rect.width = player->texture.width;
    player->texture_rect.height = player->texture.height;
    player->texture_rect.x = player->rect.x + (player->rect.width - player->texture.width);
    player->texture_rect.y = player->rect.y + (player->rect.height - player->texture.height);
}

// Function to handle player's horizontal movements and horizontal collisions
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr)
{
    if (IsKeyDown(KEY_A))
    {
        player->velocity.x = -player->speed;
        player->facing_right = false;
        player->status = "run";
    }
    else if (IsKeyDown(KEY_D))
    {
        player->velocity.x = player->speed;
        player->facing_right = true;
        player->status = "run";
    }
    else
    {
        player->velocity.x = 0;
        player->status = "idle";
    }

    player->rect.x += player->velocity.x * GetFrameTime();

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
        player->velocity.y = -player->jump_power;
        player->on_ground = false;
    }

    player->velocity.y += player->gravity;
    player->rect.y += player->velocity.y * GetFrameTime();
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

// Function to get animation from texture_store
// According to the player->status value
TextureStore *get_animation(TextureStore *texture_store, Player *player)
{
    char *status = player->status;

    if (strcmp(status, "jump") == 0)
    {
        player->frame_speed = 0.15f;
        return get_textures(texture_store, "character_no_sword_jump");
    }
    else if (strcmp(status, "fall") == 0)
    {
        player->frame_speed = 0.15f;
        return get_textures(texture_store, "character_no_sword_fall");
    }
    else if (strcmp(status, "land") == 0)
    {
        player->frame_speed = 0.15f;
        return get_textures(texture_store, "character_no_sword_land");
    }
    else if (strcmp(status, "run") == 0)
    {
        player->frame_speed = 0.2f;
        return get_textures(texture_store, "character_no_sword_run");
    }
    else if (strcmp(status, "hit") == 0)
    {
        player->frame_speed = 0.15f;
        return get_textures(texture_store, "character_no_sword_hit");
    }
    else
    {
        player->frame_speed = 0.15f;
        return get_textures(texture_store, "character_no_sword_idle");
    }
}

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

    if (camera->target.x < (camera->offset.x / camera->zoom))
        camera->target.x = (camera->offset.x / camera->zoom);

    if (camera->target.x > map_width - (camera->offset.x / camera->zoom))
        camera->target.x = map_width - (camera->offset.x / camera->zoom);

    if (camera->target.y > map_height - (camera->offset.y / camera->zoom))
        camera->target.y = map_height - (camera->offset.y / camera->zoom);
}
