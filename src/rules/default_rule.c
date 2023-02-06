#include "default_rule.h"

int default_cell_match(const struct world* w, unsigned int i, unsigned int j){
    (void)w;
    (void)i;
    (void)j;
    return 1;
}

unsigned int default_change_to_undefined(unsigned int idx){
    (void)idx;
    return UNDEFINED;
}

unsigned int default_change_to_empty(unsigned int idx){
    (void)idx;
    return EMPTY;
}


int default_change_dz(unsigned int idx){
    (void)idx;
    return 0;
}

int default_change_dz_one(unsigned int idx){
    (void)idx;
    return 1;
}

int default_change_dz_mone(unsigned int idx){
    (void)idx;
    return -1;
}