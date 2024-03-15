#include "../include/resources.h"
#include <stdio.h>
#include <stdlib.h>

Resources initResources() {
    return (Resources){.printers = 2, .scanners = 1, .modems = 1, .cdDrives = 2, .memoryAvailable = 960};
}

int allocateResources(Resources* systemResources, Process process) {
    if (systemResources->printers < process.numPrinters || systemResources->scanners < process.numScanners ||
        systemResources->modems < process.numModems || systemResources->cdDrives < process.numCDs ||
        systemResources->memoryAvailable < process.memorySize) {
        return 0;
    }
    systemResources->printers -= process.numPrinters;
    systemResources->scanners -= process.numScanners;
    systemResources->modems -= process.numModems;
    systemResources->cdDrives -= process.numCDs;
    systemResources->memoryAvailable -= process.memorySize;
    return 1;
}

void freeResources(Resources* systemResources, Process process) {
    systemResources->printers += process.numPrinters;
    systemResources->scanners += process.numScanners;
    systemResources->modems += process.numModems;
    systemResources->cdDrives += process.numCDs;
    systemResources->memoryAvailable += process.memorySize;
}

int allocateMemory(Resources* systemResources, int memorySize) {
    if (systemResources->memoryAvailable < memorySize) {
        return 0;
    }
    systemResources->memoryAvailable -= memorySize;
    return 1;
}

void freeMemory(Resources* systemResources, int memorySize) {
    systemResources->memoryAvailable += memorySize;
}
