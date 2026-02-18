#include "../main.h"

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

CSVRead *read_csv(const FileRead *file)
{
    CSVRead *csv = malloc(sizeof(CSVRead));
    csv->rows = file->lines;
    csv->erorr = 0;
    csv->data = malloc(sizeof(char **) * file->lines);

    for (size_t i = 0; i < csv->rows; i++)
    {
        char *line = file->data[i];

        char **row = malloc(sizeof(char *) * MORE_CHARS);
        int col_index = 0;

        char buffer[MORE_CHARS];
        int char_count = 0;

        for (size_t j = 0; j <= strlen(line); j++)
        {
            char c = line[j];

            if (c == ',' || c == '\n' || c == '\0')
            {
                if (char_count > 0 || c == ',')
                {
                    buffer[char_count] = '\0';

                    row[col_index] = malloc(char_count + 1);
                    strcpy(row[col_index], buffer);

                    col_index++;
                    char_count = 0;
                }

                if (c == '\0' || c == '\n')
                {
                    break;
                }

                continue;
            }

            buffer[char_count++] = c;
        }

        csv->data[i] = realloc(row, sizeof(char *) * col_index);
    }

    return csv;
};

void forget_csv(CSVRead *csv)
{
    for (size_t i = 0; i < csv->rows; i++)
    {
        for (int j = 0; csv->data[i][j] != NULL; j++)
            free(csv->data[i][j]);
        free(csv->data[i]);
    }

    free(csv->data);
    free(csv);
}
