#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

void enqueue(QueueNode** head, Process process) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for enqueue.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = process;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        QueueNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

Process dequeue(QueueNode** head) {
    if (*head == NULL) {
        fprintf(stderr, "Attempt to dequeue from an empty queue.\n");
        return (Process){0}; 
    }
    QueueNode* tempNode = *head;
    Process process = tempNode->data;
    *head = tempNode->next;
    free(tempNode);
    return process;
}
