#ifndef DISPATCHER_H
#define DISPATCHER_H
#define MAX_PRIORITY_LEVELS 3

#include "queue.h"  // Ensure this path is correct based on your project structure

// Update the function signature to accept an array of user queues for multiple priorities
void readDispatchList(const char* filename, QueueNode** realTimeQueue, QueueNode* userQueues[MAX_PRIORITY_LEVELS]);

#endif // DISPATCHER_H
