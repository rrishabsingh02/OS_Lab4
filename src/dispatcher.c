#include "../include/dispatcher.h"
#include "../include/process.h"
#include <stdio.h>
#include <stdlib.h>

void readDispatchList(const char* filename, QueueNode** realTimeQueue, QueueNode** userQueue) {
    FILE* file = fopen("dispatch_list.txt", "r");
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
            enqueue(userQueue, tempProcess);
        }
    }

    // Check if the loop exited due to an error or premature EOF
    if (scanResult != EOF && scanResult != 8) {
        fprintf(stderr, "Error reading dispatch list. The file format may be incorrect or the file is corrupted.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}
