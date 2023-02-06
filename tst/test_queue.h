#ifndef __TEST_QUEUE_H__
#define __TEST_QUEUE_H__

#include <assert.h>
#include "../src/tools/queue.h"
#include "../src/rule.h"

/**
 * @brief Tests all functionnalities of the queue.
 * If the test on one functionality passes, it displays
 * a message saying so.
 * 
 * Otherwise, the programm breaks thanks to an assert.
 * 
 */
void test_queue();

#endif // __TEST_QUEUE_H__
