#include "simulation_rule.h"

#include <stdlib.h>
#include <math.h>


#define EXPLOSION_RADIUS 7

/**
 * Useful functions
 **/

int distance(int x1, int y1, int x2, int y2){
    return (int)sqrt((x1 - x2) * (x1 -x2) + (y1 - y2) * (y1 - y2));
}


/**
 * Static Datas 
 **/ 

enum computing_state_enum {
    CELL_UNDEFINED=2, CELL_FALL, CELL_BLOCKED, CELL_RECURSION_START
};

struct cell_frame_data {
    enum computing_state_enum falling_state;
    int medium_probability;
    int is_exploding;
};

struct cell_frame_data frame_data[WIDTH * HEIGHT];


void init_falling_frame_data(){
    for (int i = 0; i < WIDTH * HEIGHT; ++i){
        frame_data[i].falling_state = CELL_UNDEFINED;
        // 1/5 chance
        frame_data[i].medium_probability = rand() % 5 == 0;

        frame_data[i].is_exploding = CELL_UNDEFINED;
    }
}


/**
 * General Checks 
 **/ 


int is_exploding(const struct world *world, int i, int j){
    if (frame_data[j * WIDTH + i].is_exploding != CELL_UNDEFINED) 
            return frame_data[j * WIDTH + i].is_exploding;

    for (int ind = 0; ind < WIDTH * HEIGHT; ++ind){
        frame_data[ind].is_exploding = 0;
    }

    int exploI = -1;
    int exploJ = -1;
    // For each detected explosion cell exploding we compute exploding surrounding cells
    for (int ind = 0; ind < WIDTH * HEIGHT; ++ind){
        if (explosion_match(world, ind % WIDTH, ind / WIDTH)){
            exploI = ind % WIDTH;
            exploJ = ind / WIDTH;

            if (exploI >= 0 && exploJ >=0){
                for (int indJ = 0; indJ < HEIGHT; ++indJ){
                    for (int indI = 0; indI < WIDTH; ++indI){
                        // dist between explosion and cell < 0
                        frame_data[indJ * WIDTH + indI].is_exploding 
                            = (distance(exploI, exploJ, indI, indJ) <= EXPLOSION_RADIUS); 
                    }
                }
            }  
        }
    } 

    return frame_data[j * WIDTH + i].is_exploding;
}


int is_fallable_block(const struct world* w, unsigned i, unsigned j){
    enum cell_type_enum type = color_to_type(w->t[j * WIDTH + i]);
    // Not a fallableBlock if it explode
    if (is_exploding(w, i, j)){
        return 0;
    }

    return (type == SAND || type == ROUGH_SAND);
}


int check_fallable_slide_left(const struct world* w,
                    unsigned int i, unsigned int j){
    if (!is_fallable_block(w, i, j))
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, -1, 1, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED);
}


int check_fallable_slide_right(const struct world* w,
                    unsigned int i, unsigned int j){
    if (!is_fallable_block(w, i, j))
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, 1, 1, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED);
}


int fallable_type_fall_match( const struct world* w,
                            unsigned int i, unsigned int j){

    if (!is_fallable_block(w, i, j))
        return 0;

    if (frame_data[j * WIDTH + i].falling_state != CELL_UNDEFINED) 
        return frame_data[j * WIDTH + i].falling_state == CELL_FALL
            || frame_data[j * WIDTH + i].falling_state == CELL_RECURSION_START;

    frame_data[j * WIDTH + i].falling_state = CELL_RECURSION_START;
    
    int coordX, coordY;
    new_coordonate(i, j, 0, 1, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    int is_sand_falling_under = fallable_type_fall_match(w, coordX, coordY)
                                || check_fallable_slide_left(w, coordX, coordY)
                                || check_fallable_slide_right(w, coordX, coordY);

    frame_data[j * WIDTH + i].falling_state 
            = (type == EMPTY || type == UNDEFINED || is_sand_falling_under) ? CELL_FALL : CELL_BLOCKED;

    return frame_data[j * WIDTH + i].falling_state == CELL_FALL;
}

/**
 * SAND RULES
 **/

int sand_fall_match(const struct world* w,
              unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != SAND)
        return 0; 

    return fallable_type_fall_match(w, i, j);
}


int sand_slide_left_match(const struct world* w,
                    unsigned int i, unsigned int j){ 
    if (color_to_type(w->t[j * WIDTH + i]) != SAND)
        return 0; 

    return !fallable_type_fall_match(w, i, j) 
        && check_fallable_slide_left(w, i, j)
        && !check_fallable_slide_right(w, i, j);
}


int sand_slide_right_match(const struct world* w,
                    unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != SAND)
        return 0; 

    return !fallable_type_fall_match(w, i, j) 
        && !check_fallable_slide_left(w, i, j) 
        && check_fallable_slide_right(w, i, j);
}


int sand_swap_rough_match(const struct world* w,
                    unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != SAND)
        return 0;    

    if (fallable_type_fall_match(w, i, j)
        || check_fallable_slide_left(w, i, j) 
        || check_fallable_slide_right(w, i, j))
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, 0, -1, &coordX, &coordY);

    if (fallable_type_fall_match(w, coordX, coordY)
        || check_fallable_slide_left(w, coordX, coordY) 
        || check_fallable_slide_right(w, coordX, coordY))
        return 0;
    if (color_to_type(w->t[coordY * WIDTH + coordX]) != ROUGH_SAND)  
        return 0;
     
    //printf("%d\n", frame_data[coordY * WIDTH + coordX].medium_probability);

    return frame_data[coordY * WIDTH + coordX].medium_probability;
}


unsigned int sand_change_to(unsigned int idx){
    switch(idx){
        case 1:
            return rgb_to_color(199, 195, 72);
        case 2:
            return rgb_to_color(217, 211, 59);
        case 0:
        default:
            return rgb_to_color(207, 202, 67);
    }
}



/**
 * ROUGH SAND RULES
 **/

int rough_sand_fall_match(const struct world* w,
              unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != ROUGH_SAND)
        return 0; 

    return fallable_type_fall_match(w, i, j);
}


int rough_sand_slide_left_match(const struct world* w,
                    unsigned int i, unsigned int j){ 
    if (color_to_type(w->t[j * WIDTH + i]) != ROUGH_SAND)
        return 0; 

    return !fallable_type_fall_match(w, i, j) 
        && check_fallable_slide_left(w, i, j) 
        && !check_fallable_slide_right(w, i, j);
}


int rough_sand_slide_right_match(const struct world* w,
                    unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != ROUGH_SAND)
        return 0; 
    
    return !fallable_type_fall_match(w, i, j) 
        && !check_fallable_slide_left(w, i, j) 
        && check_fallable_slide_right(w, i, j);
}


int rough_swap_sand_match(const struct world* w,
                    unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != ROUGH_SAND)
        return 0;    

    if (fallable_type_fall_match(w, i, j)
        || check_fallable_slide_left(w, i, j) 
        || check_fallable_slide_right(w, i, j)
        || is_exploding(w, i, j))
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, 0, 1, &coordX, &coordY);

    if (fallable_type_fall_match(w, coordX, coordY)
        || check_fallable_slide_left(w, coordX, coordY) 
        || check_fallable_slide_right(w, coordX, coordY)
        || is_exploding(w, i, j))
        return 0;

    if (color_to_type(w->t[coordY * WIDTH + coordX]) != SAND)  
        return 0;

    return frame_data[j * WIDTH + i].medium_probability;
}


unsigned int rough_sand_change_to(unsigned int idx){
    switch(idx){
        case 1:
            return rgb_to_color(176, 142, 83);
        case 2:
            return rgb_to_color(173, 138, 78);
        case 0:
        default:
            return rgb_to_color(189, 151, 87);
    }
}


/**
 * EXPLOSION RULES
 **/


int explosion_match(const struct world* w,
                    unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != EXPLOSION) return 0;

    return (frame_data[j * WIDTH + i].medium_probability);
}


int explosion_material_match(const struct world* w,
                    unsigned int i, unsigned int j){

    int type = color_to_type(w->t[j * WIDTH + i]);
    if (type == SAND || type == ROUGH_SAND || type == STONE || type == WATER){
        return is_exploding(w, i, j);
    }

    return 0;
}