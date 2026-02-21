#include "../main.h"

bool string_to_bool(const char *val)
{
    if (val == NULL)
        return false;
    else if (strcmp(val, "true") == 0)
        return true;
    else
        return false;
}