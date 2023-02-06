#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "test_world_from_file.h"

/**
 * @brief Displays the world given into argument.
 * 
 * @param w pointer to struct world
 */
void display_test_world(const struct world *w)
{
    printf("#\n");

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            printf("%d", type_to_color(w->t[i * WIDTH + j]));

            if (j != WIDTH - 1)
                printf(" ");
        }

        printf("\n");
    }
}


/**
 * @brief Loads a world (the user has to check it is the correct world).
 * 
 */
void test_world_from_file()
{
    char *path_to_world = "res/empty.txt";
    struct world w;
    init_simulation(&w, path_to_world);

    load_world_from_txt(path_to_world, &w);
    replace_type_by_random_color(&w);

    //printf("%d %d\n", WIDTH, HEIGHT);

    //display_test_world(&w);
}


/**
 * @brief Saves a world to a text file (the user has to check it is correctly written).
 * 
 */
void test_world_to_file()
{
    struct world w;
    init_simulation(&w, "res/empty.txt");

    int top_left[2] = {0, 0};
    int bottom_right[2] = {WIDTH - 1, HEIGHT - 1};

    fill_with(&w, EMPTY, top_left, bottom_right);

    top_left[1] = HEIGHT - 1;
    fill_randomly_with(&w, STONE, top_left, bottom_right);

    top_left[1] = 0;
    bottom_right[1] = 3;
    fill_randomly_with(&w, SAND, top_left, bottom_right);

    save_world_as_txt("res/test_falling_sand.txt", &w);
}


void test_world_file_manager()
{
    printf("\n## Test World File Manager ##\n");

    printf("-> World from file : ...\n");
    test_world_from_file();
    printf("->OK<-\n\n");

    printf("-> World to file : ...\n");
    test_world_to_file();
    printf("->OK<-\n\n");
}