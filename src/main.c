#include "dispatcher.h"
#include "process.h"
#include "queue.h"
#include "resources.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY_LEVELS 3  // with the assumption that there are only three priority levels for user processes

// Helper function to check if any user queue is not empty
int anyUserQueueNotEmpty(QueueNode* userQueues[MAX_PRIORITY_LEVELS]) {
    for (int i = 0; i < MAX_PRIORITY_LEVELS; i++) {
        if (userQueues[i] != NULL) {
            return 1; // found a non-empty queue
        }
    }
    return 0; // all queues are empty
}

void executeProcess(Process process) {
    printf("Executing Process - Arrival Time: %d, Priority: %d, Processor Time: %d seconds, Memory Size: %d Mbytes",
           process.arrivalTime, process.priority, process.processorTime, process.memorySize);
    printf(", Printers: %d, Scanners: %d, Modems: %d, CDs: %d\n",
           process.numPrinters, process.numScanners, process.numModems, process.numCDs);
    
    
 
}

void requeueProcessWithAdjustedPriority(QueueNode* userQueues[MAX_PRIORITY_LEVELS], Process process) {
    if (process.priority < MAX_PRIORITY_LEVELS - 1) {
        process.priority++;
    }
    enqueue(&userQueues[process.priority - 1], process); // Use updated priority, accounting for off-by-one in priority levels
}



int main() {
    QueueNode* realTimeQueue = NULL;
    QueueNode* userQueues[MAX_PRIORITY_LEVELS] = {NULL}; // Array for user process queues
    Resources systemResources = initResources();

    printf("Please enter the dispatch list file path: ");
    char filePath[260];
    scanf("%s", filePath);

    readDispatchList(filePath, &realTimeQueue, userQueues); 

    while (realTimeQueue != NULL || anyUserQueueNotEmpty(userQueues)) {
        Process processToRun = {0};
        int processFound = 0;

        // check the real-time queue first
        if (realTimeQueue != NULL) {
            processToRun = dequeue(&realTimeQueue);
            processFound = 1;
        } 
        // then iterate through user queues based on priority
        else {
            for (int i = 0; i < MAX_PRIORITY_LEVELS && !processFound; i++) {
                if (userQueues[i] != NULL) {
                    processToRun = dequeue(&userQueues[i]);
                    processFound = 1;
                }
            }
        }

        if (processFound) {
            // This segment goes inside the if (processFound) block
            if (allocateResources(&systemResources, processToRun) && allocateMemory(&systemResources, processToRun.memorySize)) {
                executeProcess(processToRun);
                // Assume process completes successfully here for simplicity
                freeResources(&systemResources, processToRun);
                freeMemory(&systemResources, processToRun.memorySize);
            } else {
                printf("Unable to allocate resources/memory for process: Arrival Time %d. Re-queuing process.\n", processToRun.arrivalTime);
                // Only requeue if the process has not been adjusted to the lowest priority yet
                if (processToRun.priority < MAX_PRIORITY_LEVELS - 1) {
                    requeueProcessWithAdjustedPriority(userQueues, processToRun);
                } else {
                    printf("Process at lowest priority cannot be allocated resources: Arrival Time %d. Dropping process.\n", processToRun.arrivalTime);
                    // Optionally handle the dropping logic here
                }
            }

        }
    }

    return 0;
}


