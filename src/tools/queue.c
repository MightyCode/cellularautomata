#include "queue.h"

int is_queue_empty(struct queue *q){
    assert(q != NULL);
    
    return q->size_of_queue == 0;
}


int is_queue_full(struct queue *q){
    assert(q != NULL);

    return q->size_of_queue >= MAX_SIZE_OF_QUEUE;
}


void init_queue(struct queue *q){
    assert(q != NULL);
    
    q->size_of_queue = 0;
    q->index_of_first = 0;
}


int push_queue(struct queue *q, struct rule *r, int x, int y){
    assert(q != NULL);
    assert(r != NULL);
    if (is_queue_full(q))
        return 0;
    
    int index = (q->index_of_first + q->size_of_queue) % MAX_SIZE_OF_QUEUE;
    
    q->array[index].r = r;
    q->array[index].x = x;
    q->array[index].y = y;
    
    ++q->size_of_queue;

    return 1;
}


int pop_queue(struct queue *q, struct rule **r, int *x, int *y){
    assert(q != NULL);
    assert(r != NULL);
    assert(x != NULL);
    assert(y != NULL);
    if (is_queue_empty(q))
        return 0;
    
    (*r) = q->array[q->index_of_first].r;
    (*x) = q->array[q->index_of_first].x;
    (*y) = q->array[q->index_of_first].y;
    
    q->index_of_first = (q->index_of_first + 1) % MAX_SIZE_OF_QUEUE;
    --q->size_of_queue;

    return 1;
}
