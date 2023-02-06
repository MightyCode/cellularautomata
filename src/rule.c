#include "rule.h"

#include "celltype.h"
#include "world/world_util.h"

#include "rules/default_rule.h"
#include "rules/game_life.h"
#include "rules/simulation_rule.h"
#include "rules/compression_rule.h"


typedef int (*rule_match_ptr)(const struct world* w, unsigned int i, unsigned int j);
typedef unsigned int (*rule_change_to_ptr)(unsigned int idx);
typedef int (*rule_change_dz)(unsigned int idx);


struct rule {
    int rule_number;
    
    rule_match_ptr rule_match;
    int rule_num_changes;
    rule_change_to_ptr rule_change_to;
    rule_change_dz rule_change_dx;
    rule_change_dz rule_change_dy;

};

static struct rule RULES[RULES_SIZE];


void rules_init(){
    if(SET_OF_RULES == 0){
        struct rule kill_cell  = {
            .rule_number = 0,
            .rule_match = &kill_cell_match,
            .rule_num_changes = 1,
            .rule_change_to = &kill_rule_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };
        struct rule revive_cell  = {
            .rule_number = 1,
            .rule_match = &revive_cell_match,
            .rule_num_changes = 3,
            .rule_change_to = &revive_rule_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };
    
        RULES[0] = kill_cell;
        RULES[1] = revive_cell;
    } else if (SET_OF_RULES == 1) {
        struct rule sand_fall  = {
            .rule_number = 0,
            .rule_match = &sand_fall_match,
            .rule_num_changes = 3,
            .rule_change_to = &sand_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz_one
        };
        
        struct rule sand_glide_left = {
            .rule_number = 1,
            .rule_match = &sand_slide_left_match,
            .rule_num_changes = 3,
            .rule_change_to = &sand_change_to,
            .rule_change_dx = &default_change_dz_mone,
            .rule_change_dy = &default_change_dz_one
        };

        struct rule sand_glide_right = {
            .rule_number = 2,
            .rule_match = &sand_slide_right_match,
            .rule_num_changes = 3,
            .rule_change_to = &sand_change_to,
            .rule_change_dx = &default_change_dz_one,
            .rule_change_dy = &default_change_dz_one
        };

                
        RULES[0] = sand_fall;
        RULES[1] = sand_glide_left;
        RULES[2] = sand_glide_right;

        struct rule rough_sand_fall  = {
            .rule_number = 3,
            .rule_match = &rough_sand_fall_match,
            .rule_num_changes = 3,
            .rule_change_to = &rough_sand_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz_one
        };
        
        struct rule rough_sand_glide_left = {
            .rule_number = 4,
            .rule_match = &rough_sand_slide_left_match,
            .rule_num_changes = 3,
            .rule_change_to = &rough_sand_change_to,
            .rule_change_dx = &default_change_dz_mone,
            .rule_change_dy = &default_change_dz_one
        };

        struct rule rough_sand_glide_right = {
            .rule_number = 5,
            .rule_match = &rough_sand_slide_right_match,
            .rule_num_changes = 3,
            .rule_change_to = &rough_sand_change_to,
            .rule_change_dx = &default_change_dz_one,
            .rule_change_dy = &default_change_dz_one
        };

        RULES[3] = rough_sand_fall;
        RULES[4] = rough_sand_glide_left;
        RULES[5] = rough_sand_glide_right;


        struct rule sand_swap_rough  = {
            .rule_number = 6,
            .rule_match = &sand_swap_rough_match,
            .rule_num_changes = 3,
            .rule_change_to = &rough_sand_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };
        
        struct rule rough_swap_sand = {
            .rule_number = 7,
            .rule_match = &rough_swap_sand_match,
            .rule_num_changes = 3,
            .rule_change_to = &sand_change_to,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };

        RULES[6] = sand_swap_rough;
        RULES[7] = rough_swap_sand;


        struct rule explosion  = {
            .rule_number = 8,
            .rule_match = &explosion_match,
            .rule_num_changes = 1,
            .rule_change_to = &default_change_to_empty,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };
        
        struct rule explosion_material = {
            .rule_number = 9,
            .rule_match = &explosion_material_match,
            .rule_num_changes = 1,
            .rule_change_to = &default_change_to_empty,
            .rule_change_dx = &default_change_dz,
            .rule_change_dy = &default_change_dz
        };

        RULES[8] = explosion;
        RULES[9] = explosion_material;

    } else {
        struct rule red_cell  = {
            .rule_number = 0,
            .rule_match = &red_cell_match,
            .rule_num_changes = 1,
            .rule_change_to = &red_change_to,
            .rule_change_dx = &default_change_dz_one,
            .rule_change_dy = &default_change_dz
        };
    
        struct rule blue_cell  = {
            .rule_number = 1,
            .rule_match = &blue_cell_match,
            .rule_num_changes = 1,
            .rule_change_to = &blue_change_to,
            .rule_change_dx = &default_change_dz_mone,
            .rule_change_dy = &default_change_dz
        };

        struct rule orange_cell  = {
            .rule_number = 2,
            .rule_match = &orange_cell_match,
            .rule_num_changes = 1,
            .rule_change_to = &orange_change_to,
            .rule_change_dx = &default_change_dz_one,
            .rule_change_dy = &default_change_dz
        };
    
        struct rule yellow_cell  = {
            .rule_number = 3,
            .rule_match = &yellow_cell_match,
            .rule_num_changes = 1,
            .rule_change_to = &yellow_change_to,
            .rule_change_dx = &default_change_dz_mone,
            .rule_change_dy = &default_change_dz
        };
    
        RULES[0] = red_cell;
        RULES[1] = blue_cell;
        RULES[2] = orange_cell;
        RULES[3] = yellow_cell;
    }
}


unsigned int rules_count() { 
    return RULES_SIZE;
}


struct rule * rule_get(unsigned int i){
    return &RULES[i];
}


int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j){
    
    return r->rule_match(w, i, j);
}


unsigned int rule_num_changes(const struct rule* r){
    return r->rule_num_changes;
}


unsigned int rule_change_to(const struct rule* r, unsigned int idx){
    return r->rule_change_to(idx);
}


int rule_change_dx(const struct rule* r, unsigned int idx){
    return r->rule_change_dx(idx);
}


int rule_change_dy(const struct rule* r, unsigned int idx){
    return r->rule_change_dy(idx);
}
