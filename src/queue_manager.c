#include "../include/queue.h"
#include <stdio.h>
#include <stdlib.h>

void enqueue(QueueNode** head, Process process) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for enqueue operation.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = process;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode; // If the queue is empty, the new node becomes the head.
    } else {
        // Traverse to the end of the queue and insert the new node.
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
        return (Process){0}; // Returning an empty process as a signal of an empty queue.
    }
    QueueNode* tempNode = *head;
    Process process = tempNode->data; // Copy the process data before freeing the node.
    *head = tempNode->next; // Remove the node from the queue.
    free(tempNode);
    return process;
}
