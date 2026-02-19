#include "../main.h"

TextureStore *load_textures()
{
    FileRead *file = load_file("assets/textures.csv");
    CSVRead *csv = read_csv(file);

    // csv->rows - 1 is to skip the header row
    TextureStore *texture_store = malloc(sizeof(TextureStore) * (csv->rows - 1));

    // i = 1 at start to skip the header
    for (unsigned int i = 1; i < csv->rows; i++)
    {
        char *type = strdup(csv->data[i][0]);
        char *name = strdup(csv->data[i][2]);
        unsigned int total_frames = atoi(csv->data[i][1]);

        Texture2D *frames = calloc(total_frames, sizeof(Texture2D));

        for (unsigned int frame_index = 0; frame_index < total_frames; frame_index++)
        {
            char path_buffer[512];
            snprintf(path_buffer, sizeof(path_buffer), "%s%i.png", csv->data[i][3], frame_index);

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
            frames,
        };
    }

    unload_file(file);
    forget_csv(csv);

    return texture_store;
}