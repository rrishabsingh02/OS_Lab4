#include "../include/dispatcher.h"
#include "../include/process.h"
#include <stdio.h>
#include <stdlib.h>

void readDispatchList(const char* filename, QueueNode** realTimeQueue, QueueNode* userQueues[MAX_PRIORITY_LEVELS]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Process tempProcess;
    int scanResult = 0;
    // Adjusted to better handle potential malformed lines or premature EOF
    while ((scanResult = fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d\n",
                  &tempProcess.arrivalTime, &tempProcess.priority,
                  &tempProcess.processorTime, &tempProcess.memorySize,
                  &tempProcess.numPrinters, &tempProcess.numScanners,
                  &tempProcess.numModems, &tempProcess.numCDs)) == 8) {
        // Prioritize enqueueing based on the process type
        if (tempProcess.priority == 0) {
            enqueue(realTimeQueue, tempProcess);
        } else {
            // Adjust for user processes to be enqueued according to their priority
            // Ensuring priority is within bounds
            int queueIndex = tempProcess.priority - 1; // Assuming user priority starts at 1
            if (queueIndex < 0 || queueIndex >= MAX_PRIORITY_LEVELS) {
                fprintf(stderr, "Invalid priority level %d for process. Adjusting to within bounds.\n", tempProcess.priority);
                queueIndex = queueIndex < 0 ? 0 : MAX_PRIORITY_LEVELS - 1; // Adjust if out of bounds
            }
            enqueue(&userQueues[queueIndex], tempProcess);
        }
    }

    // Check if the loop exited due to an error or premature EOF
    if (scanResult != EOF && scanResult != 8) {
        fprintf(stderr, "Error reading dispatch list. The file format may be incorrect or the file is corrupted.\n");
    }

    fclose(file);
}
