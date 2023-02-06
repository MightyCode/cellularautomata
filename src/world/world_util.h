#ifndef __WORLD_UTIL_H__
#define __WORLD_UTIL_H__

#include <stdio.h>

#include "../world.h"
#include "../celltype.h"

// Depending on RULES we define different RULES and rules

#ifndef SET_OF_RULES
#define SET_OF_RULES 0
#endif

#if SET_OF_RULES == 0
#define RULES_SIZE 2
#elif SET_OF_RULES == 1
#define RULES_SIZE 10
#else
#define RULES_SIZE 4
#endif

#define PATTERN_SIZE 8
#define DEFAULT_LEN 4

/**
 * @brief Applies offsets to the current coordinates of a particule to determine
 * the new coordinates of the particle. These new coordinates are put into new_x
 * and new_y. If one of the coordinates exceeds the bounds of the world, it circles
 * back in a thoric way, as if the opposite bounds were connected.
 * 
 * If the pointer to one of the new coordinate is NULL, the function breaks thanks 
 * to an assert.
 * 
 * @param x current horizontal coordinate
 * @param y current vertical coordinate
 * @param offsetX offset to the horizontal coordinate
 * @param offsetY offset to the veritcal coordinate
 * @param new_x pointer to new horizontal coordinate
 * @param new_y pointer to new vertical coordinate
 */
void new_coordonate(int, int, int, int, int *, int *);


/**
 * @brief Checks the 8 cells directly surrounding the particle at coordinates (i,j) and counts
 * the number of particles of the given type.
 * 
 * If the pointer to the world is NULL, the function breaks thanks to an assert.
 * 
 * @param w pointer to struct world
 * @param i horizontal coordinate of the particle
 * @param j vertical coordinate of the particle
 * @param type_of_cell enum cell_type_enum
 * @return The number of cells of the given type surrounding the particle.
 */
int count_surrounding_cells(const struct world*,
			    unsigned int, unsigned int, unsigned int);


/**
 * @brief Creates a rectangle between to points and fills it with particles the given type.
 * 
 * @param w pointer to struct world
 * @param type type of cells the block will be filled with
 * @param top_left coordinates of the top left corner of the block (array of size 2)
 * @param bottom_right coordinates of the bottom rigth corner of the block (array of size 2)
 */
void fill_with(struct world *, enum cell_type_enum, int [], int []);


/**
 * @brief Creates a rectangle between to points and fills it with particles of
 * the given type. Each particle will have a color randomly chosen from the set
 * of colors associated to the given type.
 * 
 * 
 * 
 * @param w pointer to struct world
 * @param type type of cells the block will be filled with
 * @param top_left coordinates of the top left corner of the block (array of size 2)
 * @param bottom_right coordinates of the bottom rigth corner of the block (array of size 2)
 */
void fill_randomly_with(struct world *, enum cell_type_enum, int [], int []);


/**
 * @brief Converts a type to a random color associated to this type for each cell
 * of the world.
 * 
 * If the pointer to the world is NULL, the function breaks thanks to an assert. 
 * 
 * @param w pointer to struct world
 */
void replace_type_by_random_color(struct world *);


#endif // __WORLD_UTIL_H__
