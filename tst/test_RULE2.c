#include "test_RULE2.h"

/**
 * @brief Counts the number of particles of each type at the beginning
 * of the simulation. For each frame of the simulation, if the number 
 * of particles is different from the original number, the programm
 * breaks thanks to an assert.
 * 
 */
void test_compression()
{
    struct world w;
    init_simulation(&w, "res/empty.txt");
    rules_init();

    load_world_from_txt("res/compression_test.txt", &w);

    int count_red = count_color(&w, RED);
    int count_blue = count_color(&w, BLUE);
    int count_orange = count_color(&w, ORANGE);
    int count_yellow = count_color(&w, YELLOW);
    int number_of_loops = 50;

    for (int i = 0; i < number_of_loops; ++i)
    {
        one_loop(&w);
        assert(count_red== count_color(&w, RED));
        assert(count_blue == count_color(&w, BLUE));
        assert(count_orange == count_color(&w, ORANGE));
        assert(count_yellow == count_color(&w, YELLOW));
    }
}

void test_compression_rules()
{

    printf("\n## Test Rule 2 ##\n");

    printf("-> Testing Compression Issues : ...\n");
    test_compression();
    printf("->OK<-\n\n");
}