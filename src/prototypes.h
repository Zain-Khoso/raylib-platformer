#pragma once

#include "types.h"

// Utilities prototypes
bool string_to_bool(const char *val);

// File reader prototypes
FileRead *load_file(const char *path);
void unload_file(FileRead *file);

CSVRead *read_csv(const FileRead *file);
void forget_csv(CSVRead *csv);

// Asset manager prototypes
TextureStore *load_textures();
void unload_textures(TextureStore *texture_store);
TextureStore *get_textures(TextureStore *texture_store, const char *query);

// Player prototypes
Player *create_player(TextureStore *texture_store);
void delete_player(Player *player);
void animate_player(TextureStore *texture_store, Player *player);
void player_horizontal_movement_collision(Player *player, TileNode *list_ptr);
void player_vertical_movement_collision(Player *player, TileNode *list_ptr);
TextureStore *get_animation(TextureStore *texture_store, Player *player);

// Camera prototypes
Camera2D create_camera(Player *player);
void update_camera(Camera2D *camera, Player *player);

// Sprite prototypes
TileNode *create_sprites(struct Player *player);
void delete_sprites(TileNode **list_ptr);
