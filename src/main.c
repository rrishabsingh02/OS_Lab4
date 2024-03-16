#include "dispatcher.h"
#include "process.h"
#include "queue.h"
#include "resources.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY_LEVELS 3  // Example: three priority levels for user processes

void executeProcess(Process process) {
    printf("Executing process: Arrival Time %d, Priority %d, Processor Time %d, Remaining Time %d\n",
           process.arrivalTime, process.priority, process.processorTime, process.remainingProcessorTime);
    // Simulate processing time reduction or complete the task as needed.
    // For simplicity in this example, we'll assume it always completes.
}

// Function to requeue process with adjusted priority if needed.
void requeueProcessWithAdjustedPriority(QueueNode* userQueues[MAX_PRIORITY_LEVELS], Process process) {
    // Adjust priority if not already at the lowest level and requeue.
    if (process.priority < MAX_PRIORITY_LEVELS - 1) {
        process.priority++;
    }
    enqueue(&userQueues[process.priority], process);
}

int main() {
    QueueNode* realTimeQueue = NULL;
    QueueNode* userQueues[MAX_PRIORITY_LEVELS] = {NULL}; // Array for user process queues
    Resources systemResources = initResources();

    printf("Please enter the dispatch list file path: ");
    char filePath[260];
    scanf("%s", filePath);

    readDispatchList(filePath, &realTimeQueue, userQueues); // Adjusted call

    while (realTimeQueue != NULL || anyUserQueueNotEmpty(userQueues)) {
        Process processToRun = {0};
        int processFound = 0;

        // Check real-time queue first
        if (realTimeQueue != NULL) {
            processToRun = dequeue(&realTimeQueue);
            processFound = 1;
        } 
        // Then iterate through user queues based on priority
        else {
            for (int i = 0; i < MAX_PRIORITY_LEVELS && !processFound; i++) {
                if (userQueues[i] != NULL) {
                    processToRun = dequeue(&userQueues[i]);
                    processFound = 1;
                }
            }
        }

        if (processFound) {
            if (allocateResources(&systemResources, processToRun) && allocateMemory(&systemResources, processToRun.memorySize)) {
                executeProcess(processToRun);
                freeResources(&systemResources, processToRun);
                freeMemory(&systemResources, processToRun.memorySize);
            } else {
                printf("Unable to allocate resources/memory for process: Arrival Time %d. Re-queuing process.\n", processToRun.arrivalTime);
                requeueProcessWithAdjustedPriority(userQueues, processToRun);
            }
        }
    }

    return 0;
}

// Helper function to check if any user queue is not empty
int anyUserQueueNotEmpty(QueueNode* userQueues[MAX_PRIORITY_LEVELS]) {
    for (int i = 0; i < MAX_PRIORITY_LEVELS; i++) {
        if (userQueues[i] != NULL) {
            return 1; // Found a non-empty queue
        }
    }
    return 0; // All queues are empty
}
