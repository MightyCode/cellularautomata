#include "compression_rule.h"


int red_cell_match(const struct world* w, unsigned int i, unsigned int j){
    if (w->t[j * WIDTH + i] != RED)
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, 1, 0, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED);
}

unsigned int red_change_to(unsigned int idx){
    (void)idx;
    return LAST_COLOR;
}

int orange_cell_match(const struct world* w, unsigned int i, unsigned int j){
    if (w->t[j * WIDTH + i] != ORANGE)
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, 1, 0, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED || w->t[coordY * WIDTH + coordX] == RED);
}

unsigned int orange_change_to(unsigned int idx){
    (void)idx;
    return LAST_COLOR;
}


int blue_cell_match(const struct world* w, unsigned int i, unsigned int j){
    if (w->t[j * WIDTH + i] != BLUE)
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, -1, 0, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED);
}

unsigned int blue_change_to(unsigned int idx){
    (void)idx;
    return LAST_COLOR;
}

int yellow_cell_match(const struct world* w, unsigned int i, unsigned int j){
    if (w->t[j * WIDTH + i] != YELLOW)
        return 0;

    int coordX, coordY;
    new_coordonate(i, j, -1, 0, &coordX, &coordY);

    unsigned int type = color_to_type(w->t[coordY * WIDTH + coordX]);

    return (type == EMPTY || type == UNDEFINED || w->t[coordY * WIDTH + coordX] == BLUE);
}

unsigned int yellow_change_to(unsigned int idx){
    (void)idx;
    return LAST_COLOR;
}



