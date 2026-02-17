#include "../main.h"

// Function to initial create the player
Player create_player()
{
    Image image_0 = LoadImage("./assets/textures/character/no_sword/idle/0.png");
    ImageAlphaCrop(&image_0, 0);
    Image image_1 = LoadImage("./assets/textures/character/no_sword/idle/1.png");
    ImageAlphaCrop(&image_1, 0);
    Image image_2 = LoadImage("./assets/textures/character/no_sword/idle/2.png");
    ImageAlphaCrop(&image_2, 0);
    Image image_3 = LoadImage("./assets/textures/character/no_sword/idle/3.png");
    ImageAlphaCrop(&image_3, 0);
    Image image_4 = LoadImage("./assets/textures/character/no_sword/idle/4.png");
    ImageAlphaCrop(&image_4, 0);

    Texture2D texture_0 = LoadTextureFromImage(image_0);
    Texture2D texture_1 = LoadTextureFromImage(image_1);
    Texture2D texture_2 = LoadTextureFromImage(image_2);
    Texture2D texture_3 = LoadTextureFromImage(image_3);
    Texture2D texture_4 = LoadTextureFromImage(image_4);

    Rectangle rect = {
        .width = texture_0.width,
        .height = texture_0.height,
        .x = 0,
        .y = 0,
    };

    UnloadImage(image_0);
    UnloadImage(image_1);
    UnloadImage(image_2);
    UnloadImage(image_3);
    UnloadImage(image_4);

    return (Player){
        .velocity = {0, 0},
        .texture_pos = {rect.x, rect.y},
        .rect = rect,
        .color = WHITE,

        .textures = {
            texture_0,
            texture_1,
            texture_2,
            texture_3,
            texture_4,
        },

        .on_ground = false,
        .frame = 1.0f,
    };
}

// Function to animate the player
void animate_player(Player *player)
{
    player->frame += PLAYER_FRAME_SPEED;

    if (player->frame > 4.0f)
    {
        player->frame = 0.0f;
    }

    player->texture = player->textures[(int)player->frame];

    player->texture_pos.x = player->rect.x + (player->rect.width - player->texture.width);
    player->texture_pos.y = player->rect.y + (player->rect.height - player->texture.height);
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
        player->velocity.y = -PLAYER_JUMP_POWER;
        player->on_ground = false;
    }

    player->velocity.y += GRAVITY;
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
