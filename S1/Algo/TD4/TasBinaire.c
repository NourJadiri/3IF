#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int allocated; /* current allocation of array */
    int filled;    /* number of items present in the binheap */
    int *array;/* array of values */
}Queue;

/* Init allocates the structure Queue and
 * also the membre array with the given size
 * it also fills allocated (size) and initializes
 * filled to 0 */
Queue * Init(int size);

/* InsertValue insert value into the binary heap
 * the array is reallocated if necessary (allocated changed
 * with respect to the new size )
 * filled is incremented by 1 */
void InsertValue(Queue * heap, int value);

/* ExtractMAx returns 0 if the binary heap is empty
 * otherwise it returns 1 and fills *val with the maximum
 * value present in the binary heap
 * filled is decremented by 1  and the max value is removed
 * from the binary heap */
int ExtractMax(Queue * heap, int * res);

/* Destroy frees the structure and the array */
void Destroy(Queue * heap);

/*Cette fonction sera super utile hihi*/
void swap(int *xp, int *yp);

int main(void)
{
    char lecture[100];
    int val;
    Queue * heap;
    heap = Init(10);

    fscanf(stdin,"%99s",lecture);
    while (strcmp(lecture,"bye")!=0) {
        if (strcmp(lecture,"insert")==0) {
            fscanf(stdin,"%99s",lecture);
            val = strtol(lecture,NULL,10);
            InsertValue(heap,val);
        } else if (strcmp(lecture,"extract")==0) {
            if(ExtractMax(heap,&val))
            {
                printf("%d\r\n",val);
            }
        }
        fscanf(stdin,"%99s",lecture);
    }
    Destroy(heap);
    return 0;
}

Queue * Init(int size)
{
    Queue *heap1;
    heap1 = (Queue*)malloc(sizeof(Queue));
    heap1 -> allocated = size;
    heap1 -> filled = 0;
    heap1 -> array = (int*)malloc(sizeof(int) * size);

    return heap1;
}

// Voir si un tas binaire est toujours ordonné
void InsertValue(Queue * heap, int value)
{
    if (heap->filled == heap->allocated){
        heap->allocated *= 2;
        heap->array = (int*) realloc(heap->array,sizeof(int)*heap->allocated); // ON OUBLIE PAS LE SIZEOF!!!
    }
    heap -> array[heap->filled] = value;
    heap -> filled++;

    int i = heap -> filled - 1;

    while(heap->array[(i-1)/2] < heap->array[i]){
        swap(&(heap->array[i]),&(heap->array[(i-1)/2]));
        i = (i-1)/2;
    }

}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int ExtractMax(Queue * heap, int *res)
{
    if(heap->filled == 0) return 0;

    *res = heap->array[0];

    heap->array[0] = heap->array[heap->filled - 1];
    heap->array[heap->filled-1] = 0;
    int i = 0;

    heap->filled--;

    while(heap->array[i] < heap->array[2*i+1] || heap->array[i] < heap->array[2*i+2]){
        if(2*i+1 < heap->filled && 2*i+2 < heap->filled){ //les deux fils existent
            if(heap->array[2*i+1] < heap->array[2*i+2]) swap(&heap->array[i],&heap->array[2*i+2]);
            else swap(&heap->array[i],&heap->array[2*i+1]);
        }

        //si ya uniquement fils gauche
        else if (2*i+1 < heap->filled && 2*i+2 >= heap->filled) swap(&heap->array[i],&heap->array[2*i+1]);

        else break;

        i++;
    }

    return 1;
}

void Destroy(Queue * heap)
{
    free(heap->array);
    free(heap);
}