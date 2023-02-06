#include "game_life.h"

/*
 * KILL FUNCTIONS
 */

int kill_cell_match(const struct world* w,
              unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != FILLED)
        return 0;
    
    int alive = count_surrounding_cells(w, i, j, FILLED);
    //printf("\n%d\n", (alive != 2 && alive != 3));    
    
    return (alive != 2 && alive != 3);
}


unsigned int kill_rule_change_to(unsigned int idx){
    if (idx == 0)
        return BLACK;
    else 
        return UNDEFINED;
}


/*
 * REVIVE FUNCTIONS
 */

int revive_cell_match(const struct world* w,
                unsigned int i, unsigned int j){
    if (color_to_type(w->t[j * WIDTH + i]) != EMPTY)
        return 0;
    
    int alive = count_surrounding_cells(w, i, j, FILLED);
    //printf("%d\n", alive);
    
    return (alive == 3);   
}


unsigned int revive_rule_change_to(unsigned int idx){
    if (idx == 0)
        return WHITE;
    else if (idx == 1)
        return RED;
    else if (idx == 2)
        return BLUE;
    else
	    return UNDEFINED;
}