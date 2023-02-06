#ifndef __CELLTYPE_H__
#define __CELLTYPE_H__

#define BLACK rgb_to_color(0, 0, 0)
#define WHITE rgb_to_color(255, 255, 255)
#define RED rgb_to_color(255, 0, 0)
#define BLUE rgb_to_color(0, 0, 255)
#define GREEN rgb_to_color(0, 255, 0)
#define YELLOW rgb_to_color(255,250,205)
#define ORANGE rgb_to_color(255,165,0)

/**
 * @brief Enumeration of integers associated to names of cell types.
 * 
 */
enum cell_type_enum {
        UNDEFINED=16777216, 
        EMPTY, FILLED, 
        SAND, ROUGH_SAND, 
        STONE, 
        WATER, 
        EXPLOSION,
        SIZE_CELL_TYPE_ENUM, LAST_COLOR, FIRST_CELL_TYPE=UNDEFINED
};

/**
 * @brief Converts RGB values into the correct color code.
 * 
 * @param red int between 0 and 255
 * @param green int between 0 and 255
 * @param blue int between 0 and 255
 * @return The color (unsigned int) associated to the given RGB values. 
 */
unsigned int rgb_to_color(int, int, int);


/**
 * @brief Gives the color associated to a given type.
 * 
 * @param type enum cell_type_enum
 * @return The color (unsigned int) associated to the given type.
 */
unsigned int type_to_color(enum cell_type_enum);


/**
 * @brief Gives a random color from the set of colors associated to a type.
 * 
 * @param type enum cell_type_enum
 * @return A random color (unsigned int) associated to the given type. 
 */
unsigned int type_to_random_color(enum cell_type_enum);


/**
 * @brief Gives the type associated to a color.
 * 
 * @param color unsigned int associated to a color through the color code
 * @return The type associated to the given color.
 */
enum cell_type_enum color_to_type(unsigned int);

#endif // __CELLTYPE_H__
