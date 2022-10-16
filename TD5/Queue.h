#include "Node.h"
#include <stdlib.h>

#ifndef INC_3IF_QUEUE_H
#define INC_3IF_QUEUE_H

typedef struct{
    Node *front,*rear;
}Queue;

Queue* Init();

void InsertValue(Queue* q, int val);

int Dequeue(Queue* q);

void Destroy(Queue* q);
#endif //INC_3IF_QUEUE_H
