#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <assert.h>
#include "../world/world_util.h"
#include "../rule.h"

#define MAX_SIZE_OF_QUEUE (RULES_SIZE * WIDTH * HEIGHT)

struct queue_object{
    struct rule *r; // rule applied to a particule
    int x;          // horizontal coordinate of a particule
    int y;          // vertical coordinate of a particle
};
struct queue {
    struct queue_object array[MAX_SIZE_OF_QUEUE];
    
    int size_of_queue;
    int index_of_first;
};

/**
 * @brief Checks if the queue is empty and returns an integer.
 * 
 * If the pointer to the queue is NULL, the function breaks thanks to an assert.
 * 
 * @param q pointer to struct queue
 * @return 1 if the queue is empty, 0 otherwise.
 */
int is_queue_empty(struct queue *);


/**
 * @brief Checks if the queue is full and returns an integer.
 * 
 * If the pointer to the queue is NULL, the function breaks thanks to an assert.
 * 
 * @param q pointer to struct queue
 * @return 1 if the queue is full, 0 otherwise.
 */
int is_queue_full(struct queue *);


/**
 * @brief Takes an existing queue and sets its size to 0 and the index of the first element to 0.
 * 
 * If the pointer to the queue is NULL, the function breaks thanks to an assert.
 * 
 * @param q pointer to struct queue
 */
void init_queue(struct queue *);


/**
 * @brief Adds a new element to a queue (a pointer to a rule and two integers x and y) 
 * and returns a status to check if the action was successful.
 * 
 * If the pointer to the queue or the rule are NULL, the function breaks thanks to an assert.
 * 
 * @param q pointer to struct queue
 * @param r pointer to struct rule
 * @param x horizontal coordinate of the particle
 * @param y vertical coordinate of the particle
 * @return 1 if the push was successful, 0 if the queue is already full.
 */
int push_queue(struct queue *, struct rule *, int, int);


/**
 * @brief Puts all informations of the first element in variables given in arguments and 
 * increases the index of the first element. If index of the first element is the index of
 * the last element of the array (MAX_SIZE_OF_QUEUE), it circles back to the index of the 
 * first element of the array (0). The functions returns a status to check if the action was
 * successful.
 * 
 * If one of the pointers given in arguments is NULL, the function breaks thanks to an assert.
 * 
 * @param q pointer to struct queue
 * @param r pointer to pointer to struct rule
 * @param x pointer to int (horizontal coordinate of the particle)
 * @param y pointer to int (vertical coordinate of the particle)
 * @return 1 if the pop was successful, 0 if the queue is already empty.
 */
int pop_queue(struct queue *, struct rule **, int *, int *);


#endif // __QUEUE_H__
