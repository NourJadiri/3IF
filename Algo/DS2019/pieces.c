#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b);

int partition(int array[], int low, int high);

void quickSort(int array[], int low, int high);

void printArray(int array[], int size);

int main(){

    int nb_billets , somme_a_rendre ;

    scanf("%d",&nb_billets);

    int *billets = (int*)malloc(nb_billets*sizeof(int));

    int i;
    for(i = 0 ; i < nb_billets ; i++){
        scanf("%d",&billets[i]);
    }
    quickSort(billets,0,nb_billets-1); //sort le array rendra la tache plus facile

    //printf("Billets triés : ");

    //printArray(billets,nb_billets);

    scanf("%d",&somme_a_rendre);

    int DP[somme_a_rendre + 1];


    DP[0] = 0;

    for(i = 1 ; i <= somme_a_rendre ; i++){
        int nb_billet_min = nb_billets; //je set le nombre optimal de billets sur le nombre max possible (somme_à_rendre si j'avais que des billets de 1)

        int j;
        for(j = 0 ; j < nb_billets ; j++){

            if(i - billets[j] < 0) continue; //ne pas considérer quand je suis out of bounds

            /*
             * On itère dans le tableau en vérifiant à chaque fois si combien de billets je dois rendre à DP[i - billets[j]]
             * On rajoute 1 au nombres de billets rendus
             * puis on prend le minimum de toutes ces valeurs
             */
            if(DP[i - billets[j]] < nb_billet_min) nb_billet_min = DP[i - billets[j]] + 1;
        }
        DP[i] = nb_billet_min;
    }

    printf("%d\r\n",DP[somme_a_rendre]);


    return 0;
}

/*Soit un système de monnaie S, défini par les types de billet de valeur b1, b2, …, bn,
avec b1, b2, …, bn des entiers positifs. L’objectif est de rendre une somme N (nombre
entier positif) de façon optimale, c'est-à-dire avec le nombre minimal de billets.*/


// function to swap elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    int j;
    for (j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

// function to print array elements
void printArray(int array[], int size) {
    int i;

    for (i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

