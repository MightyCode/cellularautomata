#include "simulation.h"

#include "../world/world_from_file.h"
#include "../rules/init_rules.h"


/**
 * INIT FUNCTIONS
 */

void init_simulation_info(struct simulation_info *sim)
{
    char *str = "res/";
    for (int i = 0; i < DEFAULT_LEN; ++i)
        sim->path_to_world[i] = str[i];
    sim->path_to_world[DEFAULT_LEN] = '\0';

    sim->image_number = 0;
    sim->seed = 0;
    sim->show_all_maps = 0;
}


void init_simulation(struct world *world, char *path_to_world)
{
    int from[2] = {0, 0};
    int to[2] = { WIDTH - 1, HEIGHT - 1};
    (void) from;
    (void) to;


    switch (SET_OF_RULES) {
        case 0:
            for (int i = 0; i < WIDTH * HEIGHT; ++i) {
                if (rand() % 2){
                    world->t[i] = EMPTY;
                } else {
                    world->t[i] = FILLED;
                }
            }

            replace_type_by_random_color(world);

            break;
        case 1:
            if (strlen(path_to_world) == DEFAULT_LEN) {
                if (WIDTH == 40 && HEIGHT == 30)
                    load_world_from_txt("res/sand_stone_water.txt", world);
                else 
                    fill_randomly_with(world, EMPTY, from, to);
                
            } else {
                load_world_from_txt(path_to_world, world);
            }

            replace_type_by_random_color(world);

            break;
        case 2:
            load_world_from_txt("res/compression_test.txt", world);
            break;
    }
}


/**
 * UPDATES FUNCTIONS
 */

/**
 * @brief Browses all cells of the world. If the current rule can be
 * applied, it is added to the queue, alogside the coordinates of the
 * current cell.
 * 
 * @param world pointer to struct world
 * @param queue pointer to struct queue
 */
void fill_queue(struct world *world, struct queue *queue) {   
    struct rule *current_rule;

    for (unsigned int rul = 0; rul < rules_count(); ++rul) {
        current_rule = rule_get(rul);

        for (unsigned int j = 0; j < HEIGHT; ++j) {
            for (unsigned int i = 0; i < WIDTH; ++i) {
                if (rule_match(world, current_rule, i, j)) {
                    push_queue(queue, current_rule, i, j);
                }
            }
        }
    }
}


enum application_enum {
    RECURSION_NONE, RECURSION_PASSED, RECURSION_BROKEN
};

enum application_enum applications [WIDTH * HEIGHT];


/**
 * @brief Sets all elements of applications to RECURSION_NONE.
 * 
 */
void init_application_enum(){
    for (int i = 0; i < WIDTH * HEIGHT; ++i){
        applications[i] = RECURSION_NONE;
    }
}


/**
 * @brief Modifies the applications array.
 * 
 * If there are no modifications to a cell, no change is needed.
 * 
 * If the cell has already been visited by a recursion, we've found a cycle :
 * the applications array cell is changed to RECURSION_BROKEN.
 * 
 * If the cell has never been visited by a recursion, the applications array
 * cell is changed to RECURSION_PASSED.
 * 
 * @param world pointer to struct world
 * @param modification_size array of integers, each element is associated
 *                          with the number of cells that can move there
 * @param modifications_dest array of struct modification_destination, contains
 *                          the coordinates and types of cells that can move there
 * @param modifications_src array of struct modification_source, contains the
 *                          coordinates of the cell where the particle can go and which
 *                          should be check for movement 
 * @param i coordinates of the cell (i = x + y * WIDTH)
 */
void apply_modification_one_cell(struct world *world, int modification_size[],
                           struct modification_destination modifications_dest[],
                           struct modification_source modifications_src[], unsigned int i)
{

    int numbers_of_changement = modification_size[i];
    if (numbers_of_changement == 0)
        return;

    // check if we are in loop recursion
    if (applications[i] == RECURSION_PASSED){
        applications[i] = RECURSION_BROKEN;
        return;
    } else {
        applications[i] = RECURSION_PASSED;
    }
    

    struct modification_source modification_src = modifications_src[i];
    // The modification of the i-current cell, depent of another cell which start from the i-current cell
    // Tho we try to modify it before
    int source = modification_src.toY * WIDTH + modification_src.toX;
    if (modification_src.shouldCheck)
    {
        apply_modification_one_cell(world, modification_size, modifications_dest, modifications_src, source);

        if (applications[source] == RECURSION_BROKEN){
            applications[i] = RECURSION_BROKEN;
        }
    }


    // Make modification_size_empty
    modification_size[i] = 0;
    // If the current cell is not empty we can't move the cell to that one
    if (color_to_type(world->t[i]) != EMPTY && applications[i] != RECURSION_BROKEN)
    {
        return;
    }

    int pointer = i * RULES_SIZE * 10;
    int index_choosed;
    if (numbers_of_changement == 1)
        index_choosed = 0;
    else
        index_choosed = rand() % numbers_of_changement;

    struct modification_destination modification_choosed = modifications_dest[pointer + index_choosed];

    int cell_depart = modification_choosed.fromY * WIDTH + modification_choosed.fromX;

    if (applications[i] != RECURSION_BROKEN)
        world->t[cell_depart] = EMPTY;
    world->t[i] = modification_choosed.color;
}


/**
 * @brief  Tries to pass recuursion for each cell of the world.
 * 
 * @param world pointer to struct world
 * @param modification_size array of integers, each element is associated
 *                          with the number of cells that can move there
 * @param modifications_dest array of struct modification_destination, contains
 *                          the coordinates and types of cells that can move there
 * @param modification_src array of struct modification_source, contains the
 *                          coordinates of the cell where the particle can go and which
 *                          should be check for movement 
 */
void apply_modification_to_world(struct world *world,
                       int modification_size[],
                       struct modification_destination modifications_dest[],
                       struct modification_source modification_src[])
{
    // Fix compressibility problem
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        apply_modification_one_cell(world, modification_size, modifications_dest, modification_src, i);
    }
}


/**
 * @brief Empties the queue and makes associated changes to cells.
 * 
 * @param world pointer to srtuct world
 * @param queue pointer to struct queue
 */
void make_queue_changements(struct world *world, struct queue *queue)
{
    int from_x, from_y;
    int to_x, to_y;
    struct rule *current_rule;

    int modification_size[WIDTH * HEIGHT] = {};
    struct modification_destination modifications_dest[WIDTH * HEIGHT * RULES_SIZE * 10] = {};
    struct modification_source modifications_src[WIDTH * HEIGHT] = {};
    
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        modifications_src[i].shouldCheck = 0;
    }

    while (pop_queue(queue, &current_rule, &from_x, &from_y))
    {
        int changes = rule_num_changes(current_rule);

        int idx = rand() % changes;
        unsigned int changeTo = rule_change_to(current_rule, idx);
        if (changeTo == LAST_COLOR)
        {
            changeTo = world->t[from_y * WIDTH + from_x];
        }

        int offset_x = rule_change_dx(current_rule, idx);
        int offset_y = rule_change_dy(current_rule, idx);

        // Not a particule we change it immedialty
        if (offset_x == 0 && offset_y == 0)
        {
            world->t[from_y * WIDTH + from_x] = changeTo;

            // Is a particule, we add it the list of modification dest (cell destination)
            // and add to the list of modification source (where the cell came from)
        }
        else
        {
            struct modification_destination modification_destination = {
                .fromX = from_x,
                .fromY = from_y,
                .color = changeTo};

            new_coordonate(from_x, from_y, offset_x, offset_y, &to_x, &to_y);

            struct modification_source modification_source = {
                .toX = to_x,
                .toY = to_y,
                .shouldCheck = 1};

            int idx_dest = to_y * WIDTH + to_x;
            modifications_dest[idx_dest * RULES_SIZE * 10 + modification_size[idx_dest]] = modification_destination;
            modification_size[idx_dest] += 1;

            modifications_src[from_y * WIDTH + from_x] = modification_source;
        }
    }

    apply_modification_to_world(world, modification_size, modifications_dest, modifications_src);
}


/**
 * @brief Creates and initializes the queue of rules, 
 * initializes the application array and sets all falling
 * states to undefined.
 * 
 * Fills the queue with all rules that can be applied.
 * Empties the queue and makes changes according to those rules.
 * 
 * @param world pointer to struct world
 */
void update(struct world *world)
{
    // Init frame data
    struct queue queue;
    init_queue(&queue);

    init_all_rule_for_frame();
    init_application_enum();

    // Do simulations
    fill_queue(world, &queue);
    make_queue_changements(world, &queue);
}

/**
 * OTHERS FUNCTIONS
 */

/**
 * @brief Prints colors of each cells into the standard output with
 * the WIDTH * HEIGHT format so that it can be used by SDL.
 * 
 * @param w pointer to struct world
 */
void display(const struct world *w)
{
    for (int j = 0; j < HEIGHT; ++j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {   
            printf("%d", type_to_color(w->t[j * WIDTH + i]));

            if (i != WIDTH - 1)
                printf(" ");
        }

        printf("\n");
    }
}


/**
 * @brief Updates the world and displays it into the standard output.
 * 
 * @param image_number number of frame to display
 * @param world pointer to struct world
 */
void loop(int image_number, struct world *world)
{
    for (int image_count = 0; image_count < image_number; ++image_count)
    {
        update(world);
        display(world);
    }
}


void run_simulation(struct simulation_info *sim)
{   
    rules_init();

    struct world world;
    init_simulation(&world, sim->path_to_world);

    display(&world);
    loop(sim->image_number, &world);
}


void one_loop(struct world *world)
{
    update(world);
}