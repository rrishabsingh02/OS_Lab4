
#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int arrivalTime;
    int priority;
    int processorTime;
    int memorySize;
    int numPrinters;
    int numScanners;
    int numModems;
    int numCDs;
} Process;

#endif // PROCESS_H
