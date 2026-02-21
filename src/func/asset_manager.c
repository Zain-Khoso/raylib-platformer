#include "../main.h"

TextureStore *load_textures()
{
    FileRead *file = load_file("assets/textures.csv");
    CSVRead *csv = read_csv(file);

    if (csv->rows <= 1)
    {
        unload_file(file);
        forget_csv(csv);
        return NULL;
    }

    // csv->rows - 1 is to skip the header row and + 1 for the null terminator
    TextureStore *texture_store = calloc(csv->rows, sizeof(TextureStore));

    // i = 1 at start to skip the header
    for (unsigned int i = 1; i < csv->rows; i++)
    {
        char *type = strdup(csv->data[i][0]);
        char *name = strdup(csv->data[i][3]);
        bool repeat = string_to_bool(csv->data[i][1]);
        unsigned int total_frames = atoi(csv->data[i][2]);

        Texture2D *frames = calloc(total_frames, sizeof(Texture2D));

        for (unsigned int frame_index = 0; frame_index < total_frames; frame_index++)
        {
            char path_buffer[512];
            snprintf(path_buffer, sizeof(path_buffer), "%s%i.png", csv->data[i][4], frame_index);

            Image image = LoadImage(path_buffer);
            if (image.data == NULL)
            {
                printf("\n\tFailed to load image: %s\n\n", path_buffer);
                continue;
            }

            ImageAlphaCrop(&image, 0);
            frames[frame_index] = LoadTextureFromImage(image);
            UnloadImage(image);
        }

        texture_store[i - 1] = (TextureStore){
            type,
            name,
            total_frames,
            repeat,
            frames,
        };
    }

    unload_file(file);
    forget_csv(csv);

    // Specifying the end of this array
    texture_store[csv->rows - 1] = (TextureStore){0};

    return texture_store;
}

void unload_textures(TextureStore *texture_store)
{
    if (texture_store == NULL)
    {
        return;
    }

    for (unsigned int i = 0; texture_store[i].type != NULL; i++)
    {
        free(texture_store[i].type);
        free(texture_store[i].name);

        for (unsigned int f = 0; f < texture_store[i].total_frames; f++)
        {
            if (texture_store[i].frames[f].id > 0)
            {
                UnloadTexture(texture_store[i].frames[f]);
            }
        }

        free(texture_store[i].frames);
    }

    free(texture_store);
}

TextureStore *get_textures(TextureStore *texture_store, const char *query)
{
    if (texture_store == NULL)
        return NULL;

    for (unsigned int i = 0; texture_store[i].type != NULL; i++)
    {
        if (strcmp(texture_store[i].name, query) == 0)
            return &texture_store[i];
    }

    return NULL;
}
