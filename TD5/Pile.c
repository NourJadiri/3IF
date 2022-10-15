#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 3

typedef struct {
    int firstIndex; // index of first elem
    int lastIndex; // index of last elem
    int *array; // array of values
} Queue;

/* Init allocates the structure Queue and
 * also the membre array with the given size
 * it also fills array with 0s */
Queue * Init();

/* InsertValue inserts value into the queue
 * if there's room for it, otherwise doesn't do anything */
void InsertValue(Queue * aQueue, int value);

/* ExtractVal returns 0 if the queue is empty
 * otherwise it returns 1 and fills *val with the next
 * value in the queue
 * the first-in value is removed from the queue */
int ExtractVal(Queue * aQueue, int * val);

/* Destroy frees the structure and the array */
void Destroy(Queue * aQueue);


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
            if(ExtractVal(aQueue, &val))
            {
                printf("%d\r\n",val);
            }
        }
        fscanf(stdin, "%99s", lecture);
    }
    Destroy(aQueue);
    return 0;
}

Queue * Init()
{
    Queue *aQueue;
    aQueue = (Queue*)malloc(sizeof(Queue));
    aQueue -> firstIndex = 0;
    aQueue -> lastIndex = 0;
    aQueue -> array = (int*)malloc(sizeof(int) * MAX_QUEUE);

    return aQueue;
}

void InsertValue(Queue * aQueue, int value)
{
    if (aQueue->lastIndex != MAX_QUEUE && aQueue->array[aQueue->lastIndex] == 0) {
        aQueue->array[aQueue->lastIndex] = value;
        aQueue->lastIndex++;
        // si fin tableau complet mais on a deja dequeue le debut du tableau
        if (aQueue->lastIndex == MAX_QUEUE && aQueue->array[0] == 0) {
            aQueue->lastIndex = 0;
        }
    }

    /*for (int i = 0; i<5; i++){
        printf("%d ", aQueue->array[i]);
    }
    printf("\n");*/
}

int ExtractVal(Queue * aQueue, int *val)
{
    // empty queue
    if (aQueue->firstIndex == aQueue->lastIndex && aQueue->array[aQueue->lastIndex] == 0) {
        return 0;
    } else {
        *val = aQueue->array[aQueue->firstIndex];
        aQueue->array[aQueue->firstIndex] = 0;
        aQueue->firstIndex++;
        // si on a atteint le bout du tableau mais pile pas remplie
        if (aQueue->firstIndex == MAX_QUEUE) {
            aQueue->firstIndex = 0;
        }
        // si fin tableau complet mais on vient de dequeue le debut du tableau
        if (aQueue->lastIndex == MAX_QUEUE && aQueue->array[0] == 0) {
            aQueue->lastIndex = 0;
        }
        /*for (int i = 0; i<5; i++){
            printf("%d ", aQueue->array[i]);
        }
        printf("\n");*/
        return 1;
    }
}

void Destroy(Queue * aQueue)
{
    free(aQueue->array);
    free(aQueue);
}