
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "queue.h"  

// Reads the dispatch list from a file and enqueues processes into the appropriate queues
void readDispatchList(const char* filename, QueueNode** realTimeQueue, QueueNode** userQueue);

#endif // DISPATCHER_H
