#include "../include/dispatcher.h"
#include "../include/process.h"
#include <stdio.h>
#include <stdlib.h>

void readDispatchList(const char* filename, QueueNode** realTimeQueue, QueueNode** userQueue) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Process tempProcess;
    while (fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d\n",
                  &tempProcess.arrivalTime, &tempProcess.priority,
                  &tempProcess.processorTime, &tempProcess.memorySize,
                  &tempProcess.numPrinters, &tempProcess.numScanners,
                  &tempProcess.numModems, &tempProcess.numCDs) == 8) {
        if (tempProcess.priority == 0) {
            enqueue(realTimeQueue, tempProcess);
        } else {
            enqueue(userQueue, tempProcess);
        }
    }
    if (!feof(file)) {
        fprintf(stderr, "Error reading file, format may be incorrect.\n");
    }

    fclose(file);
}
