#ifndef __DEFAULT_RULE_H__
#define __DEFAULT_RULE_H__

#include "../celltype.h"
#include "../world.h"
#include "../world/world_util.h"

/**
 * @brief Default rule which is always matching
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule 
 */
int default_cell_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the undefined "color" index not depending of index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int default_change_to_undefined(unsigned int);


/**
 * @brief give the empty "color" index not depending of index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int default_change_to_empty(unsigned int);


/**
 * @brief give a default deplacement of cell
 * 
 * @param index of the deplacement
 * @return int zero change
 */
int default_change_dz(unsigned int);

/**
 * @brief  give a default deplacement of cell
 * 
 * @param index of the deplacement
 * @return int one cell deplacement
 */
int default_change_dz_one(unsigned int);

/**
 * @brief give a default deplacement of cell
 * 
 * @param index of the deplacement
 * @return int minus one cell deplacement
 */
int default_change_dz_mone(unsigned int);

#endif // __DEFAULT_LIFE_H__
