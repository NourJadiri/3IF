#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(){
    int totalCapacity;
    int capacity, object; // iterator variables
    scanf("%d" , &totalCapacity);


    // read object list
    int weights[101];
    int nrOfObjects = 0;
    do {
        scanf("%d",&weights[nrOfObjects]);
    } while (weights[nrOfObjects++] != -1);
    nrOfObjects--;


    // initialisation of 2D array (first column to 1, rest 0)
    int fillable[totalCapacity + 1][nrOfObjects + 1];
    for(capacity = 0 ; capacity <= totalCapacity ; capacity++) {
        for (object = 0 ; object <= nrOfObjects ; object++) fillable[capacity][object] = capacity == 0;
    }


    // calculation of fillable_matrix
    for(object = 1 ; object <= nrOfObjects ; object++) {
        for (capacity = 1 ; capacity <= totalCapacity ; capacity++) {
            if (capacity - weights[object - 1] < 0)
                fillable[capacity][object] = fillable[capacity][object-1];
            else
                fillable[capacity][object] = fillable[capacity][object-1] ||
                                             fillable[capacity - weights[object - 1]][object - 1];
            //printf("fillable[capacity %d][object %d] = %d\r\n", capacity, object, fillable[capacity][object]);
        }
    }


    // output
    if(fillable[totalCapacity][nrOfObjects]) printf("OUI\r\n");
    else printf("NON\r\n");

    return 0; //on l'oublie pas celui la!!!!!!!
    //cc <3
}