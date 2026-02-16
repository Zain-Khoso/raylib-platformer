#include <stdlib.h>
#include <string.h>

#include "tiles.h"
#include "player.h"

const char *level_map[] = {
    "                                                                                    ",
    "                                                                                    ",
    "                                                                                    ",
    " XX    XXX            XX     XX    XXX            XX     XX    XXX            XX    ",
    " XX                          XX                          XX                         ",
    " XXXX         XX         XX  XXXX         XX         XX  XXXX         XX         XX ",
    " XXXX  P    XX               XXXX       XX               XXXX       XX              ",
    " XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX     XX    X  XXXX    XX  XX    ",
    "       X  XXXX    XX  XXX          X  XXXX    XX  XXX          X  XXXX    XX  XXX   ",
    "    XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX      XXXX  XXXXXX  XX  XXXX  ",
    "XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  XXXXXXXX  XXXXXX  XX  XXXX  ",
};

// Function to create sprites in a linked list
TileNode *create_sprites(Player *player)
{
    TileNode *list_ptr = NULL;
    int level_rows = 11; // Hardcoded to match your map rows
    int level_cols = strlen(level_map[0]);

    for (int row = 0; row < level_rows; row++)
    {
        for (int col = 0; col < level_cols; col++)
        {
            int x_pos = col * TILE_SIZE;
            int y_pos = row * TILE_SIZE;
            if (level_map[row][col] == 'X')
            {
                TileNode *new_node = malloc(sizeof(TileNode));
                new_node->rect = (Rectangle){x_pos, y_pos, TILE_SIZE, TILE_SIZE};
                new_node->color = LIGHTGRAY;
                new_node->next = list_ptr;
                list_ptr = new_node;
            }
            else if (level_map[row][col] == 'P')
            {
                player->rect.x = x_pos;
                player->rect.y = y_pos;
            }
        }
    }
    return list_ptr;
}

// Function to delete sprites and free the linked list
void delete_sprites(TileNode **list_ptr)
{
    TileNode *current = *list_ptr;
    while (current != NULL)
    {
        TileNode *next_node = current->next;
        free(current);
        current = next_node;
    }
    *list_ptr = NULL;
}
