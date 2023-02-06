#include "world_util.h"

// This pattern gives the offsests to reach all surrounding cells of a given cell.
int PATTERN_OFFSET[PATTERN_SIZE][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

void new_coordonate(int x, int y, int offsetX, int offsetY, int *new_x, int *new_y){
    if (new_x == NULL || new_y == NULL) return;

    (*new_x) = (x + offsetX + WIDTH) % WIDTH;
    (*new_y) = (y + offsetY + HEIGHT) % HEIGHT; 
}


int count_surrounding_cells(const struct world* w,
			    unsigned int i, unsigned int j, unsigned int type_of_cell){
    
    int number_of_cells = 0;
    
    int coordX = 0;
    int coordY = 0;
    
    for (int count = 0; count < PATTERN_SIZE; ++count){
        new_coordonate(i, j, PATTERN_OFFSET[count][0], PATTERN_OFFSET[count][1], &coordX, &coordY);
        if (color_to_type(w->t[coordY * WIDTH + coordX]) == type_of_cell)
            ++number_of_cells;
    }
    
    return number_of_cells;
}

void fill_with(struct world *w, enum cell_type_enum type, int top_left[], int bottom_right[]){
    int top_x = top_left[0];
    int top_y = top_left[1];
    int bottom_x = bottom_right[0];
    int bottom_y = bottom_right[1];

    for (int i = top_x; i <= bottom_x; ++i){
        for (int j = top_y; j <= bottom_y; ++j)
            w->t[i + j * WIDTH] = type;
    }
}


void fill_randomly_with(struct world *w, enum cell_type_enum type, int top_left[], int bottom_right[]){
    int top_x = top_left[0];
    int top_y = top_left[1];
    int bottom_x = bottom_right[0];
    int bottom_y = bottom_right[1];

    for (int i = top_x; i <= bottom_x; ++i){
        for (int j = top_y; j <= bottom_y; ++j){
            w->t[i + j * WIDTH] = type_to_random_color(type);
        }
    }
}


void replace_type_by_random_color(struct world *world){
    for (int i = 0; i < HEIGHT * WIDTH; ++i){
        unsigned type = color_to_type(world->t[i]);
        world->t[i] = type_to_random_color(type); 
    }
}