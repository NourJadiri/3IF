#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int allocated; /* current allcoation of array */
    int filled;    /* number of items present in the binheap */
    int *array;/* array of values */
} BinaryHeap;

/* Init allocates the structure BinaryHeap and
 * also the membre array with the given size
 * it also fill allocated (size) and intializes
 * filled to 0 */
BinaryHeap * Init(int size);

/* InsertValue insert value into the binary heap
 * the array is reallocated if necessary (allocated changed
 * with respect to the new size )
 * filled is incremented by 1 */
void InsertValue(BinaryHeap * heap, int value);

/* ExtractMAx returns 0 if the binary heap is empty
 * otherwise it return 1 and fills *val with the maximum
 * value present in the binary heap
 * filled is decremented by 1  and the max value is removed
 * from the binary heap */
int ExtractMax(BinaryHeap * heap, int * val);

/* Destroy frees the structure and the array */
void Destroy(BinaryHeap * heap);

/*Cette fonction sera super utile hihi*/
void swap(int *xp, int *yp);

int TestChildren(BinaryHeap * heap, int i);

int main(void)
{
    char lecture[100];
    int val;
    BinaryHeap * heap;
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

BinaryHeap * Init(int size)
{
    BinaryHeap *heap1;
    heap1 = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    heap1 -> allocated = size;
    heap1 -> filled = 0;
    heap1 -> array = (int*)malloc(sizeof(int) * size);

    return heap1;
}

// Voir si un tas binaire est toujours ordonné
void InsertValue(BinaryHeap * heap, int value)
{
    if (heap->filled == heap->allocated){
        heap->allocated *= 2;
        heap->array = (int*) realloc(heap->array,heap->allocated);
    }
    heap -> array[heap->filled] = value;
    heap -> filled++;

    int i = heap -> filled - 1;

    while(heap->array[(i-1)/2] < heap->array[i]){
        swap(&(heap->array[i]),&(heap->array[(i-1)/2]));
        i = (i-1)/2;
    }

    for(int j = 0 ; j < heap->filled ; j++){
        printf("%d ",heap->array[j]);
    }
    printf("\n");

}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int ExtractMax(BinaryHeap * heap, int *res)
{
    if(!heap->filled) return -1;

    int max = heap->array[0];

    swap(&(heap->array[0]),&(heap->array[heap->filled]));
    heap->filled--;
    int i = 0;

    while(TestChildren(heap,i)){
        if(TestChildren(heap,i) == 1) {
            swap((&heap->array[i]), &(heap->array[2*i+1]));
            i = 2*i+1;
        }
        else {
            swap((&heap->array[i]), &(heap->array[2*i+2]));
            i = 2*i + 2 ;
        }
    }


    return max;
}

int TestChildren(BinaryHeap * heap, int i) {
    if (2*i+1 >= heap->filled) return 0; // pas d'enfants
    if (2*i+2 >= heap->filled){ // seulement enfant a gauche
        if(heap->array[i] < heap->array[2*i+1]) return 1;
    }
    return 1 + heap->array[2*i+1] < heap->array[2*i+2];
}


void Destroy(BinaryHeap * heap)
{
    free(heap->array);
    free(heap);

}
