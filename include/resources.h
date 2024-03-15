
#ifndef RESOURCES_H
#define RESOURCES_H

#include "process.h" 

typedef struct {
    int printers;
    int scanners;
    int modems;
    int cdDrives;
    int memoryAvailable;
} Resources;

Resources initResources();

// Attempts to allocate resources for a process. Returns 1 on success, 0 on failure.
int allocateResources(Resources* systemResources, Process process);

// Frees resources allocated to a process.
void freeResources(Resources* systemResources, Process process);

// Additional functions for memory management
int allocateMemory(Resources* systemResources, int memorySize);
void freeMemory(Resources* systemResources, int memorySize);


#endif // RESOURCES_H
