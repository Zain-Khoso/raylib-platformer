#include <stdlib.h>
#include <raylib.h>

#include "player.h"
#include "tiles.h"

#define TITLE "Palm Tree Island"
#define FPS 60

int main(void)
{
    // Window setup
    InitWindow(GetScreenWidth(), GetScreenHeight(), TITLE);

    ToggleFullscreen();

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
        DrawRectangleRec(player.rect, player.color);

        EndMode2D();

        EndDrawing();
    }

    delete_sprites(&sprites_ptr);

    CloseWindow();

    return 0;
}
