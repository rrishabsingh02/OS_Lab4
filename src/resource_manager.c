#include "../include/resources.h"
#include <stdio.h>
#include <stdlib.h>

Resources initResources() {
    // Initializes the Resources structure with the specific available resources.
    return (Resources){
        .printers = 2, 
        .scanners = 1, 
        .modems = 1, 
        .cdDrives = 2, 
        // Adjusting the total memory available to match the specifications.
        .memoryAvailable = 1024  
    };
}

int allocateResources(Resources* systemResources, Process process) {
    // Check for resource availability before allocation.
    if (systemResources->printers >= process.numPrinters && 
        systemResources->scanners >= process.numScanners &&
        systemResources->modems >= process.numModems && 
        systemResources->cdDrives >= process.numCDs &&
        systemResources->memoryAvailable >= process.memorySize) {
        
        // Deduct the allocated resources from the system resources.
        systemResources->printers -= process.numPrinters;
        systemResources->scanners -= process.numScanners;
        systemResources->modems -= process.numModems;
        systemResources->cdDrives -= process.numCDs;
        systemResources->memoryAvailable -= process.memorySize;
        
        return 1; // Success
    }
    
    return 0; // Failure if resources or memory are not sufficient.
}

void freeResources(Resources* systemResources, Process process) {
    // Add the resources back to the system resources upon process completion.
    systemResources->printers += process.numPrinters;
    systemResources->scanners += process.numScanners;
    systemResources->modems += process.numModems;
    systemResources->cdDrives += process.numCDs;
    systemResources->memoryAvailable += process.memorySize;
}

int allocateMemory(Resources* systemResources, int memorySize) {
    // Check for memory availability before allocation.
    if (systemResources->memoryAvailable >= memorySize) {
        systemResources->memoryAvailable -= memorySize;
        return 1; // Success
    }
    
    return 0; // Failure if not enough memory is available.
}

void freeMemory(Resources* systemResources, int memorySize) {
    // Add the memory back to the system resources upon process completion.
    systemResources->memoryAvailable += memorySize;
}
