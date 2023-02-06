#ifndef __SIMULATION_RULE_H__
#define __SIMULATION_RULE_H__

#include "default_rule.h"

/**
 * @brief init cache for rules computations 
 * 
 */
void init_falling_frame_data();

/**
 * SAND RULES
 **/ 

/**
 * @brief give the validation of the falling sand rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int sand_fall_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the left sand sliding rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int sand_slide_left_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the right sand sliding rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int sand_slide_right_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the rule where sand cell swap with a upper rough sand cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int sand_swap_rough_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the new color of the cell according to the index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int sand_change_to(unsigned int);


/**
 * ROUGH SAND RULES
 **/ 

/**
 * @brief give the validation of the falling rough sand rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int rough_sand_fall_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the left sand sliding rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int rough_sand_slide_left_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the right sand sliding rule applied to this cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int rough_sand_slide_right_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the validation of the rule where rough sand cell swap with a lower sand cell
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int rough_swap_sand_match(const struct world*, unsigned int, unsigned int);


/**
 * @brief give the new color of the cell according to the index
 * 
 * @param index of the color
 * @return unsigned int the color of the new cell
 */
unsigned int rough_sand_change_to(unsigned int);


/**
 * EXPLOSION RULES
 **/ 

/**
 * @brief give the validation of a explosion cell exploding this frame
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int explosion_match(const struct world*, unsigned int , unsigned int );


/**
 * @brief give the validation of the explosion rule applied to cell which can explode
 * 
 * @param world pointer to struct world
 * @param x position of the tested cell
 * @param y position of the tested cell
 * @return int validation of rule
 */
int explosion_material_match(const struct world*, unsigned int , unsigned int );


#endif // __SIMULATION_RULE_H__
