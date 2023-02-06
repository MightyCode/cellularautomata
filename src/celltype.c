#include "celltype.h"

#include <stdlib.h>
#include <stdio.h>

unsigned int rgb_to_color(int r, int g, int blue){
    return r + 256 * g + 65536 * blue;
}


unsigned int type_to_color(enum cell_type_enum type){
    switch(type){
    case EMPTY:
        return BLACK;
    case FILLED:
        return WHITE;
    case SAND:
        return rgb_to_color(207, 202, 67);
    case ROUGH_SAND:
        return rgb_to_color(189, 151, 87);
    case STONE:
        return rgb_to_color(94, 105, 107);
    case WATER:
        return rgb_to_color(52, 143, 235);
    case EXPLOSION:
        return rgb_to_color(254, 0, 0);
    default:
        // Return the color by default
        return type;
    }
}


unsigned int type_to_random_color(enum cell_type_enum type){
    int random;
    
    switch(type){
        case EMPTY:
            return BLACK;
        case FILLED:
            random = rand() % 3;
            switch(random){
                case 1:
                    return RED;
                case 2:
                    return BLUE;
                case 0:
                default:
                    return WHITE;
            }
        case SAND:
            random = rand() % 3;
            switch(random){
                case 1:
                    return rgb_to_color(199, 195, 72);
                case 2:
                    return rgb_to_color(217, 211, 59);
                case 0:
                default:
                    return rgb_to_color(207, 202, 67);
            }
        case ROUGH_SAND:
            random = rand() % 3;
            switch(random){
                case 1:
                    return rgb_to_color(176, 142, 83);
                case 2:
                    return rgb_to_color(173, 138, 78);
                case 0:
                default:
                    return rgb_to_color(189, 151, 87);
            }
        case STONE:
            random = rand() % 3;
            switch(random){
                case 1:
                    return rgb_to_color(96, 108, 110);
                case 2:
                    return rgb_to_color(89, 100, 102);
                case 0:
                default:
                    return rgb_to_color(94, 105, 107);
            }
        case WATER:
            random = rand() % 3;
            switch(random){
                case 1:
                    return rgb_to_color(52, 143, 235);
                case 2:
                    return rgb_to_color(63, 149, 235);
                case 0:
                default:
                    return rgb_to_color(50, 143, 237);
            }
        case EXPLOSION:
            return rgb_to_color(254,0,0);
        default:
            // Return the color by default
            return type;
    }
}


enum cell_type_enum color_to_type(unsigned int color){
    if (color == BLACK 
     || color == EMPTY) 
        return EMPTY;
    
    // Life cell is black or red or blue
    if (color == WHITE
     || color == RED 
     || color == BLUE
     || color == FILLED) 
        return FILLED;

    if (color == rgb_to_color(207, 202, 67)
     || color == rgb_to_color(199, 195, 72)
     || color == rgb_to_color(217, 211, 59))
        return SAND;

    if (color == rgb_to_color(176, 142, 83)
     || color == rgb_to_color(173, 138, 78)
     || color == rgb_to_color(189, 151, 87))
        return ROUGH_SAND;
     

    if (color == rgb_to_color(94, 105, 107)
     || color == rgb_to_color(96, 108, 110)
     || color == rgb_to_color(89, 100, 102))
        return STONE;

    if (color == rgb_to_color(52, 143, 235)
       || color == rgb_to_color(63, 149, 235)
       || color == rgb_to_color(50, 143, 237))
       return WATER;
    
    if (color == rgb_to_color(254, 0, 0))
        return EXPLOSION;

    if(color >= FIRST_CELL_TYPE && color < FIRST_CELL_TYPE + SIZE_CELL_TYPE_ENUM)
        return color;
    
    return UNDEFINED;
}
