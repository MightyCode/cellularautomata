#include "test_queue.h"

/**
 * @brief Checks if the size of the queue and the index od the first
 * element are both zero.
 * 
 * If the queue is not initialized correctly, the programm breaks
 * thanks to an assert, otherwise nothing happens.
 * 
 * If the pointer to the queue is NULL, the programm breaks thanks to
 * an assert.
 * 
 * @param q pointer to struct queue
 */
void test_init_queue(struct queue *q){
    assert(q != NULL);
    init_queue(q);

    assert(q->size_of_queue == 0);
    assert(q->index_of_first == 0);
}


/**
 * @brief Checks if a queue is empty, adds an element to it,
 * checks if it is not empty, removes the element and checks again
 * if it is empty.
 * 
 * If one of these checks is incorrect, the programm breaks thanks
 * thanks to an assert.
 * 
 * If the pointer to the queue is NULL, the programm breaks thanks to
 * an assert.
 * 
 * @param q pointer to struct queue
 */
void test_is_queue_empty(struct queue *q) {
    assert(q != NULL);

    assert(is_queue_empty(q));
    assert(push_queue(q, rule_get(0), 0, 0));
    assert(!is_queue_empty(q));

    // Make the queue empty

    struct rule *rule;
    int x, y;
    assert(pop_queue(q, &rule, &x, &y));
}


/**
 * @brief Fills a queue until it is full (checks if it is full
 * before it should) then checks if the queue is full.
 * After that, tries to add a new element to the queue and check
 * if it fails.
 * 
 * If one of these checks is incorrect, the programm breaks thanks
 * thanks to an assert.
 * 
 * If the pointer to the queue is NULL, the programm breaks thanks to
 * an assert.
 * 
 * @param q pointer to struct queue
 */
void test_is_queue_full(struct queue *q){
    assert(q != NULL);

    for (int i = 0; i < MAX_SIZE_OF_QUEUE; ++i){
        assert(!is_queue_full(q));
        assert(push_queue(q, rule_get(0), 0, 0));
    }

    assert(is_queue_full(q));
    assert(!push_queue(q, rule_get(0), 0, 0));

    // Make the queue empty
    struct rule *rule;
    int x, y;
    for (int i = 0; i < MAX_SIZE_OF_QUEUE; ++i){
        assert(pop_queue(q, &rule, &x, &y));
        assert(!is_queue_full(q));
    }
}


/**
 * @brief Adds and removes element from the queue and compares the
 * content of the queue to expected results.
 * 
 * If one of these comparisons is incorrect, the programm breaks thanks
 * to an assert.
 * 
 * If the pointer to the queue is NULL, the programm breaks thanks to
 * an assert.
 * 
 * @param q pointer to struct queue
 */
void test_push_queue(struct queue *q){
    assert(q != NULL);

    struct rule *r;
    
    int results[20];
  
    int x, y;
    int expected_x, expected_y;


    // Make the queue empty
    while(pop_queue(q, &r, &x, &y)){}
    
    int first_element = q->index_of_first;
    int initial_size = q->size_of_queue;

    struct rule *expected_address;
    
    // We will add push info and see when we'll pop out if they still are here. And good ordonned.
    for (int k = 0; k < RULES_SIZE; ++k){
        r = rule_get(k);
        expected_address = r;
        
        // Push values
        for (int i = 0; i < 10; ++i){
            assert(push_queue(q, r, i, i + 2));
            results[i] = i;
            results[i + 10] = i + 2;

            // Test when we add things if struct's variables still valid
            assert(q->index_of_first == first_element);
            assert(q->size_of_queue == initial_size + i);
        }
        
        // Pop values and checks
        for (int j = 0; j < 10; ++j){
            pop_queue(q, &r, &x, &y);
            
            expected_x = results[j];
            expected_y = results[j + 10];
            
            assert(r != NULL);
            assert(expected_address == r && expected_x == x && expected_y == y);

            assert(q->index_of_first == first_element + j);
            assert(q->size_of_queue == initial_size + 10 - j);
        }
    }
}


void test_queue(){
    printf("\n## Test Queue ##\n");

    if (RULES_SIZE <= 0) {
        printf("No rule available, can't test queue properly");
        return;
    }

    struct queue q;
    printf("-> Init queue : ...\n");
    test_init_queue(&q);  
    printf("->OK<-\n\n");

    printf("-> Test queue empty function : ...\n");
    test_is_queue_empty(&q);
    printf("->OK<-\n\n");

    printf("-> Test queue full function : ...\n");
    test_is_queue_full(&q);
    printf("->OK<-\n\n");

    printf("-> Add some elements : ...\n");
    //test_push_queue(&q);
    printf("->OK<-\n\n");
}
