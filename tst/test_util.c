#include "test_util.h"

int count_type(const struct world *w, enum cell_type_enum type)
{
    int count = 0;
    for (int i = 0; i < WIDTH - 1; ++i)
        for (int j = 0; j < HEIGHT - 1; ++j)
            if (color_to_type(w->t[i + j * WIDTH]) == type)
                ++count;

    return count;
}

int count_color(const struct world *w, unsigned int color)
{
    int count = 0;
    for (int i = 0; i < WIDTH - 1; ++i)
        for (int j = 0; j < HEIGHT - 1; ++j)
            if (w->t[i + j * WIDTH] == color)
                ++count;

    return count;
}