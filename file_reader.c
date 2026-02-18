#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

typedef struct
{
    unsigned int erorr;
    unsigned int lines;
    char **data;
} FileRead;

FileRead *load_file(const char *path);
void unload_file(FileRead *file);

int main()
{
    FileRead *file = load_file("assets/textures.csv");
    if (file->erorr != 0)
    {
        return 1;
    }

    for (size_t i = 0; i < file->lines; i++)
    {
        printf("%s", file->data[i]);
    }

    unload_file(file);
}

FileRead *load_file(const char *path)
{
    FileRead *output = malloc(sizeof(FileRead));
    output->data = NULL;
    output->lines = 0;
    output->erorr = 0;

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("\nError opening file: %s.\n", path);

        output->erorr = 1;
        return output;
    }

    output->data = malloc(sizeof(char *) * MORE_LINES);

    size_t total_chars = 0;
    char c;

    while (true)
    {
        c = fgetc(file);

        if (ferror(file))
        {
            printf("\nError reading character: %li line: %i\n", total_chars + 1, output->lines + 1);
            printf("In file: assets/textures.csv");

            free(output->data);

            output->erorr = 1;
            output->data = NULL;
            return output;
        };

        if (feof(file))
        {
            if (total_chars != 0)
            {
                output->data[output->lines] = realloc(output->data[output->lines], total_chars + 1);
                output->data[output->lines][total_chars] = '\0';
                output->lines++;
            }

            break;
        }

        if (total_chars == 0)
        {
            output->data[output->lines] = malloc(MORE_CHARS);
        }

        output->data[output->lines][total_chars] = c;

        total_chars++;

        if (c == '\n')
        {
            output->data[output->lines] = realloc(output->data[output->lines], total_chars + 1);
            output->data[output->lines][total_chars] = '\0';

            output->lines++;
            total_chars = 0;

            if (output->lines % MORE_CHARS == 0)
            {
                size_t new_size = output->lines + MORE_CHARS;

                output->data = realloc(output->data, sizeof(char *) * new_size);
            }
        }

        else if (total_chars % MORE_CHARS == 0)
        {
            size_t new_size = total_chars + MORE_CHARS;
            output->data[output->lines] = realloc(output->data[output->lines], new_size);
        }
    };

    output->data = realloc(output->data, sizeof(char *) * output->lines);

    fclose(file);

    return output;
}

void unload_file(FileRead *file)
{
    for (size_t i = 0; i < file->lines; i++)
    {
        free(file->data[i]);
    }

    free(file->data);
    free(file);
}