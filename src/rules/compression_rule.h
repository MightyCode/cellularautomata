#ifndef __COMPRESSION_RULE_H__
#define __COMPRESSION_RULE_H__

#include "default_rule.h"

/**
 * @brief give the validation of the red cell rule
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule 
 */
int red_cell_match(const struct world*, unsigned int, unsigned int);

/**
 * @brief return last color so the color will keep
 * 
 * @param unused index
 * @return unsigned int 
 */
unsigned int red_change_to(unsigned int);


/**
 * @brief give the validation of the orange cell rule
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int orange_cell_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief return last color so the color will keep
 * 
 * @param unused index
 * @return unsigned int 
 */
unsigned int orange_change_to(unsigned int);


/**
 * @brief give the validation of the blue cell rule
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int blue_cell_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief return last color so the color will keep
 * 
 * @param unused index
 * @return unsigned int 
 */
unsigned int blue_change_to(unsigned int);

/**
 * @brief give the validation of the yellow cell rule
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int yellow_cell_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief return last color so the color will keep
 * 
 * @param unused index
 * @return unsigned int
 */
unsigned int yellow_change_to(unsigned int);


#endif // __COMPRESSION_RULE_H__