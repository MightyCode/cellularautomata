#include <stdio.h>
#include <stdlib.h>

#include "../src/tools/queue.h"
#include "../src/rule.h"
#include "test_world_util.h"
#include "test_queue.h"
#include "test_world_from_file.h"
#include "test_RULE1.h"
#include "test_RULE2.h"

int main(void)
{
    printf("\n TESTING FOR SET OF RULES %d \n\n", SET_OF_RULES);

    switch (SET_OF_RULES)
    {
    case 0:
        test_queue();
        break;
    case 1:
        test_world_util();
        test_world_file_manager();
        test_simulation_rules();
        break;
    case 2:
        test_compression_rules();
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}
