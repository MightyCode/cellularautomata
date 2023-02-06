#ifndef __WORLD_FROM_FILE_H__
#define __WORLD_FROM_FILE_H__

#include "../world.h"
#include "../celltype.h"

/**
 * @brief Takes a text file and an existing world and fills each cells of the world 
 * according to the pattern described in the file.
 * 
 * If the pointer to the world is NULL or the path is inexistant, the function breaks 
 * thanks to an assert.
 * 
 * @param path_to_text string that indicates the path to the file that will be loaded
 * @param w pointer to strcut world
 */
void load_world_from_txt(char *, struct world *);


/**
 * @brief Browses each cells of the world and saves the pattern in a text file located 
 * with the path given in arguments
 * 
 * If the pointer to the world is NULL or the path is inexistant, the function breaks 
 * thanks to an assert.
 * 
 * @param path_to_file_name string that indicates the path to the file in which the world will be saved
 * @param w pointer to struct world
 */
void save_world_as_txt(char *, struct world *);

#endif //__FROM_FILE_H__

