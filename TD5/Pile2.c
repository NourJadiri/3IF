#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "Queue.h"
#define MAX_QUEUE_SIZE 100



void toString(Queue* queue);

int main(void)
{
    char lecture[100];
    int val;
    Queue * aQueue;
    aQueue = Init();

    fscanf(stdin, "%99s", lecture);
    while (strcmp(lecture, "bye") != 0) {
        if (strcmp(lecture, "queue") == 0) {
            fscanf(stdin, "%99s", lecture);
            val = strtol(lecture,NULL,10);
            InsertValue(aQueue, val);
        } else if (strcmp(lecture, "dequeue") == 0) {
            if(Dequeue(aQueue))
            {
                printf("%d\r\n",val);
            }
        }
        fscanf(stdin, "%99s", lecture);
    }
    Destroy(aQueue);
    return 0;
}


void toString(Queue* queue){

    if(queue->front == NULL) return;

    Node* iterator = queue->front;

    //Tant que y'a un node dans ma liste, je print la valeur du node
    while(iterator->next != NULL){
        printf("%d ", iterator->value);
        iterator = iterator->next;
    }

    printf("\n\r");
}

