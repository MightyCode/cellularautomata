#include "test_world_util.h"

void test_new_coordonate(){
    int xstart = WIDTH / 2;
    int ystart = HEIGHT / 2;
  
    int xend;
    int yend;
  
    new_coordonate(xstart, ystart, 1, 1, &xend, &yend);
    
    assert(xend == xstart + 1 && yend == ystart + 1);
    printf("Matrix of size (%d, %d), coord %d %d + (1 1) =  %d %d\n", WIDTH, HEIGHT, xstart, ystart, xend, yend);
    
    new_coordonate(WIDTH-1, HEIGHT-1, 1, 1, &xend, &yend);
    
    assert(xend == 0 && yend == 0);
    printf("Matrix of size (%d, %d), coord %d %d + (1 1) =  %d %d\n", WIDTH, HEIGHT, WIDTH-1, HEIGHT-1, xend, yend);
    
    new_coordonate(0, 0, -1, -1, &xend, &yend);

    assert(xend == WIDTH-1 && yend == HEIGHT-1);
    printf("Matrix of size (%d, %d), coord %d %d - (1 1) =  %d %d\n", WIDTH, HEIGHT, 0, 0, xend, yend);
}

void test_world_util(){
    printf("\n## Test World Util ##\n");

    printf("-> New coordonate : ...\n");
    test_new_coordonate();
    printf("->OK<-\n\n");
}
