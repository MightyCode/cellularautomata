#ifndef __RUN_H__
#define __RUN_H__

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "../celltype.h"
#include "../world.h"
#include "../rule.h"
#include "../world/world_util.h"
#include "../tools/queue.h"

#define MAX_SIZE_OF_PATH 100

struct simulation_info {
	int show_all_maps;
	int image_number;
	int seed;
	char path_to_world[MAX_SIZE_OF_PATH];
};


/**
 * @brief Initializes an existing struct simulation_info by setting all
 * its attributes to default : all integers are set to 0 and the path_to_world
 * array is filled with 0s.
 * 
 * @param sim pointer to struct simulation_info
 */
void init_simulation_info(struct simulation_info *);

struct modification_destination {
	int fromX;
	int fromY;
	unsigned int color;
};

struct modification_source {
	int toX;
	int toY;
    int shouldCheck;
};


/**
 * @brief  Initializes the world according to the set of rules.
 * 
 * If the first set of rules is chosen, the world is initialized 
 * with random cells for the game of life.
 * 
 * If the second set of rules is chosen, the world described by the
 * text file located to /res/path_to_world is loaded (if path_to_world
 * is empty, a default world is loaded) and all types are replaced with random
 * colors associated to these types.
 * 
 * If the third set of rules is chosen, the compression_test file is loaded.
 * 
 * @param w pointer to struct world
 * @param path_to_world string describing the location of the file to load
 */
void init_simulation(struct world *, char *);


/**
 * @brief Initializes the rules according to the set of rules, creates
 * a world and initializes the simulation according to the simulation 
 * infos given in argument.Displays the world into the standard output
 * and updates the world until the number of frames given by the simulation 
 * infos is reached.
 * 
 * @param sim pointer to struct simulation_info
 */
void run_simulation(struct simulation_info *);


/**
 * @brief Updates one time the world given in argument. This update is made
 * according to the rules associated to the current set of rules.
 * 
 * @param world pointer to struct world
 */
void one_loop(struct world *);

#endif //__RUN_H__
