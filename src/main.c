#include "dispatcher.h"
#include "process.h"
#include "queue.h"
#include "resources.h"
#include <stdio.h>
#include <stdlib.h>

// Placeholder for process execution simulation
void executeProcess(Process process) {
    printf("Executing process: Arrival Time %d, Priority %d, Processor Time %d\n",
           process.arrivalTime, process.priority, process.processorTime);
    // Here, you might simulate processing time or perform actual task simulations.
}

int main() {
    QueueNode* realTimeQueue = NULL;
    QueueNode* userQueue = NULL; 
    Resources systemResources = initResources();

    printf("Please enter the dispatch list file path: ");
    char filePath[260];
    scanf("%s", filePath);

    readDispatchList(filePath, &realTimeQueue, &userQueue);

    // Main dispatch loop with simple time simulation
    while (realTimeQueue != NULL || userQueue != NULL) {
        Process processToRun = {0};
        int processFound = 0;

        // Real-Time processes have the highest priority
        if (realTimeQueue != NULL) {
            processToRun = dequeue(&realTimeQueue);
            processFound = 1;
        }
        // Fallback to user processes managed by a feedback queue system
        else if (userQueue != NULL) {
            processToRun = dequeue(&userQueue);
            processFound = 1;
        }

        if (processFound) {
            if (allocateResources(&systemResources, processToRun) && allocateMemory(&systemResources, processToRun.memorySize)) {
                // Simulate the process execution
                executeProcess(processToRun);
                
                // Release resources and memory after execution
                freeResources(&systemResources, processToRun);
                freeMemory(&systemResources, processToRun.memorySize);
            } else {
                // Handling for when resources or memory cannot be allocated
                printf("Unable to allocate resources/memory for process: Arrival Time %d\n", processToRun.arrivalTime);
                // Depending on your policy, you may re-queue the process or handle it differently
            }
        }

        // Simulate a time tick; could be more sophisticated with actual time tracking
    }

    return 0;
}
