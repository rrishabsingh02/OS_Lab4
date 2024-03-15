
#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"  

typedef struct QueueNode {
    Process data;
    struct QueueNode* next;
} QueueNode;

// Function to add a process to the queue
void enqueue(QueueNode** head, Process process);

// Function to remove and return a process from the queue
Process dequeue(QueueNode** head);

#endif // QUEUE_H
