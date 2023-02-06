#ifndef __TEST_RULE_1_H__
#define __TEST_RULE_1_H__

#include <assert.h>

#include "test_util.h"
#include "../src/world/world_from_file.h"
#include "../src/simulation/simulation.h"

/**
 * @brief Checks if the number of particles stays the same
 * throughout the simulation.
 * If the test passes, it displays a message saying so.
 * 
 * Otherwise, the programm breaks thanks to an assert.
 * 
 */
void test_simulation_rules();

#endif // __TEST_RULE_1_H__