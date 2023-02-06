#include "test_RULE1.h"

/**
 * @brief Counts the number of particles of each type at the beginning
 * of the simulation. For each frame of the simulation, if the number 
 * of particles is different from the original number, the programm
 * breaks thanks to an assert.
 * 
 */
void test_number_of_particles()
{
    struct world w;
    init_simulation(&w, "res/falling_sand.txt");
    rules_init();

    int count_sand = count_type(&w, SAND);
    int count_stone = count_type(&w, STONE);
    int number_of_loops = 3;

    for (int i = 0; i < number_of_loops; ++i)
    {
        one_loop(&w);
        assert(count_sand == count_type(&w, SAND));
        assert(count_stone == count_type(&w, STONE));
    }
}

void test_simulation_rules()
{

    printf("\n## Test Rule 1 ##\n");

    printf("-> Number of particles : ...\n");
    test_number_of_particles();
    printf("->OK<-\n\n");
}