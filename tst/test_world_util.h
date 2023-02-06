#ifndef __TEST_WORLD_UTIL_H__
#define __TEST_WORLD_UTIL_H__

#include <assert.h>
#include "../src/world/world_util.h"

/**
 * @brief Checks if the new_coordinates_function gives the correct cordinates.
 * If not, the programm breaks thanks to an assert
 * 
 */
void test_new_coordonate();

/**
 * @brief Calls the test_new_coordinates function.
 * If it works, it displays a message saying so.
 * 
 */
void test_world_util();

#endif // __TEST_WORLD_UTIL_H__
