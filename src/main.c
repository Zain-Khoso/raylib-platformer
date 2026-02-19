#include "main.h"

int main(void)
{
    // Window setup
    InitWindow(GetScreenWidth(), GetScreenHeight(), TITLE);

    ToggleFullscreen();

    // Loading assets
    TextureStore *texture_store = load_textures();

    // Creating sprites
    Player player = create_player();
    TileNode *sprites_ptr = create_sprites(&player);

    // Camera setup
    Camera2D camera = create_camera(&player);

    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        // Player physics
        player_horizontal_movement_collision(&player, sprites_ptr);
        player_vertical_movement_collision(&player, sprites_ptr);

        animate_player(&player);

        // Camera work
        update_camera(&camera, &player);

        // World rendering
        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode2D(camera);

        // Terrain
        for (TileNode *ptr = sprites_ptr; ptr != NULL; ptr = ptr->next)
        {
            DrawRectangleRec(ptr->rect, ptr->color);
        }

        // Player
        DrawTextureV(player.texture, player.texture_pos, player.color);

        EndMode2D();

        EndDrawing();
    }

    delete_sprites(&sprites_ptr);
    unload_textures(texture_store);

    CloseWindow();

    return 0;
}
