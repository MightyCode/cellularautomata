#ifndef __TEST_COMPRESSION_H__
#define __TEST_COMPRESSION_H__

#include <assert.h>

#include "test_util.h"
#include "../src/world/world_from_file.h"
#include "../src/celltype.h"
#include "../src/simulation/simulation.h"
#include "../src/rules/compression_rule.h"

/**
 * @brief Checks if the number of particles stays the same
 * throughout the simulation.
 * If the test passes, it displays a message saying so.
 * 
 * Otherwise, the programm breaks thanks to an assert.
 * 
 */
void test_compression_rules();

#endif //__TEST_COMPRESSION_H__