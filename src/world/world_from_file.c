#include <stdio.h>
#include <assert.h>

#include "world_from_file.h"

void load_world_from_txt(char *path_to_txt, struct world *w)
{
    FILE *source = fopen(path_to_txt, "r");
    assert(source != NULL);

    unsigned int n;
    int i = 0;

    while (fscanf(source, "%d", &n) != EOF)
    {
        assert(i < WIDTH * HEIGHT);
        w->t[i] = n;
        ++i;
    }
    
    fclose(source);
}


void save_world_as_txt(char *path_to_file_name, struct world *w)
{
    FILE *destination = fopen(path_to_file_name, "w");
    assert(destination != NULL);

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            fprintf(destination, "%d", w->t[i * WIDTH + j]);

            if (j != WIDTH - 1)
                fprintf(destination, " ");
        }
        
        fprintf(destination, "\n");
    }

    fclose(destination);
}