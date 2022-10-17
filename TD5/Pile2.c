#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "Queue.h"

#define MAX_QUEUE_SIZE 100



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

            Node* temp = newNode(aQueue->front->value);

            if(Dequeue(aQueue))
            {
                printf("%d\r\n",temp->value);

            }
            free(temp);
        }
        fscanf(stdin, "%99s", lecture);
    }
    Destroy(aQueue);
    return 0;
}




