#ifndef __INIT_RULE_H__
#define __INIT_RULE_H__

#include "default_rule.h"
#include "game_life.h"
#include "simulation_rule.h"
#include "compression_rule.h"

/**
 * @brief Init all rule for the simulation of this frame
 * It will init caches for rule computations for exemple
 * 
 */
void init_all_rule_for_frame();

#endif //__INIT_RULE_H__