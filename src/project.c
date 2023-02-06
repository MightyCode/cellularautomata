/**
 * Project.c does the interface between the user and the simulation script. 
 **/

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation/simulation.h"
#include "world/world_util.h"

#define MAX_MAP_TO_RUN 10

/**
 * @brief Copy string at index to create path of file.
 * 
 * @param s String to copy
 * @param sim simulation informations where the fonction will copy the string
 * @param idx index of character
 */
void copy_string_at_index(char *s, struct simulation_info *sim, int idx)
{
    for (unsigned int i = 0; i < strlen(s); ++i)
        sim->path_to_world[i + idx] = s[i];
}

/**
 * @brief Parse argument given by user
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @param sim simulation informations where write information from arguments
 * 
 * @return int info if the program should stop or not
 */
int parse_arguments_or_set_by_default(int argc, char *argv[], struct simulation_info *sim)
{
    sim->image_number = 3;
    sim->seed = 2;

    int opt;
    int option_index = 0;

    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"file", required_argument, 0, 'f'},
        {"frame", required_argument, 0, 'm'},
        {"seed", required_argument, 0, 's'},
        {"all", no_argument, 0, 'a'}};

    while ((opt = getopt_long(argc, argv, "msfha", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'm':
            sim->image_number = atoi(argv[optind]);
            break;
        case 's':
            sim->seed = atoi(argv[optind]);
            break;
        case 'f':
            copy_string_at_index(argv[optind], sim, DEFAULT_LEN);
            break;
        case 'a':
            sim->show_all_maps = 1;
            break;
        case 'h':
            printf("Help for the S1-sandwitch-project\n");
            printf("Arguments : \n");
            printf(" Help [-h --help]\n");
            printf(" Number of frames [-m --frame number] | per default 3\n");
            printf(" Seed [-s --seed number] | per default 2\n");
            printf(" Map file to load [-f --file filepath]. This argument work only on SRULE=1\n");
            printf("Show all map [-a --all]. This argument work only on SRULE=1\n");
            printf("Arguments in compilation :");
            printf(" Width of the map [WIDTH=number] | per default 40\n");
            printf(" Height of the map [HEIGHT=number] | per default 30\n");
            printf(" Set of rule [SRULE=number] | per default 0\n");
            printf("   .SRULE=0 load rule and map of game of life -> achiev 0 and 1\n");
            printf("   .SRULE=1 load rule and map of sand simulation -> achiev 2, 4 and 6\n");
            printf("   .SRULE=2 load rule and map for compression tests -> achiev 3 and 5\n");
            return 0;
        default:
            return 0;
        }
    }

    return 1;
}


/**
 * @brief Run pannel of all map
 * 
 * @param sim simulation informations
 */
void run_all_map(struct simulation_info *sim){
    #define FRAME_MAX = 20
    
    int number_map = 0;
    char maps[MAX_MAP_TO_RUN][MAX_SIZE_OF_PATH];
    int frames[MAX_MAP_TO_RUN];

    // Load certain map depending on the simulation's resolution
    if (WIDTH == 40 && HEIGHT == 30){
        number_map = 5;

        strcpy(maps[0], "res/test_falling_sand.txt");
        frames[0] = 40;
        strcpy(maps[1], "res/sand_stone_blocks.txt");
        frames[1] = 40;
        strcpy(maps[2], "res/falling_sand.txt");
        frames[2] = 60;
        strcpy(maps[3], "res/loop.txt");
        frames[3] = 30;
        strcpy(maps[4], "res/sand_stone_water.txt");
        frames[4] = 110;
    }

    if (number_map == 0) return;

    for (int i = 0; i < number_map; ++i){
        sim->image_number = frames[i];
        strcpy(sim->path_to_world, maps[i]);

        run_simulation(sim);
    }
}


/**
 * @brief Main, init simulation, parse arguments and lauch simulation
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @return int result of program
 */
int main(int argc, char *argv[])
{
    struct simulation_info sim;
    init_simulation_info(&sim);

    if (!parse_arguments_or_set_by_default(argc, argv, &sim))
    {
        return EXIT_FAILURE;
    }

    srand(sim.seed);

    printf("%d %d\n", WIDTH, HEIGHT);

    if (sim.show_all_maps && SET_OF_RULES == 1)
        run_all_map(&sim);
    else 
        run_simulation(&sim);

    return EXIT_SUCCESS;
}
