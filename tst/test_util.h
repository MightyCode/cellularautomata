#ifndef __TEST_UTIL_H__
#define __TEST_UTIL_H__

#include "../src/world.h"
#include "../src/celltype.h"

/**
 * @brief Counts the number of cells of a given type in the world.
 * 
 * @param w pointer to struct world
 * @param type enum cell_type_enum
 * @return The number of cells from the given type int the world.
 */
int count_type(const struct world*, enum cell_type_enum);

/**
 * @brief Counts the number of cells of a given type in the world.
 * 
 * @param w pointer to struct world
 * @param color unsigned int
 * @return The number of cells of the given color in the world.
 */
int count_color(const struct world *, unsigned int);

#endif //__TEST_UTIL_H__