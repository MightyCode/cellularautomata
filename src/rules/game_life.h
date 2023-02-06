#ifndef __GAME_LIFE_H__
#define __GAME_LIFE_H__

#include "default_rule.h"

/**
 * @brief give the validation of the rule which tell if a living cell should die
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int kill_cell_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the new color of the cell according to the index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int kill_rule_change_to(unsigned int);


/**
 * @brief give the validation of the rule which tell if a dead cell should revive
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int revive_cell_match(const struct world*, unsigned int, unsigned int);

/**
 * @brief give the new color of the cell according to the index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int revive_rule_change_to(unsigned int);

#endif // __GAME_LIFE_H__
