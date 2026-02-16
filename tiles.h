#ifndef TILES_H

#define TILES_H

#include "shared.h"

typedef struct TileNode
{
    Rectangle rect;
    Color color;
    struct TileNode *next;
} TileNode;

struct Player;

TileNode *create_sprites(struct Player *player);
void delete_sprites(TileNode **list_ptr);

#endif
