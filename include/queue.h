#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"  // Make sure this path is correct

typedef struct QueueNode {
    Process data;
    struct QueueNode* next;
} QueueNode;

void enqueue(QueueNode** head, Process process);
Process dequeue(QueueNode** head);

#endif // QUEUE_H
