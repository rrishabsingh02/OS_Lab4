#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int arrivalTime;
    int priority;
    int processorTime; // Total processor time required
    int remainingProcessorTime; // Processor time remaining. Initially, this will be equal to processorTime.
    int memorySize;
    int numPrinters;
    int numScanners;
    int numModems;
    int numCDs;
    int hasStarted; // Flag to indicate if the process has started execution, use 0 for false, 1 for true.
} Process;

#endif // PROCESS_H
