#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int knapsack2(int cap, int * tab, int size);
int doubleKnapsack(int cap1, int cap2, int * tab, int size);

// AS : à supprimer

int main(){


    // Gestion des entrées
    int cap1 , cap2 , pa , po;

    //printf("capacité libre bateau 1 :"); //AS
    scanf("%d" , &cap1);

   // printf("Capacité libre bateau 2 :"); //AS
    scanf("%d",&cap2);

    //printf("Nombre objets argent :"); //AS
    scanf("%d" , &pa);

    //printf("Nombre objets or :"); //AS
    scanf("%d", &po);

    int *ta = (int*) malloc(pa * sizeof(int));
    int *to = (int*) malloc(po * sizeof(int));

    int i;
    for(i = 0 ; i < pa ; i++){
        //printf("Objet argent %d :", i); //AS
        scanf("%d", &ta[i]);
    }

    for(i = 0 ; i < po ; i++){
        //printf("Objet or %d :", i); //AS
        scanf("%d", &to[i]);
    }

    //printf("Poids objets argent : "); //AS
    //display_array(ta,pa); //AS

    //printf("Poids objets or : "); //AS
    //display_array(to,po); //AS
    //Fin d'entrée des données


    int AO = knapsack2(cap1, ta, pa) + knapsack2(cap2, to, po);
    int OA = knapsack2(cap1, to, po) + knapsack2(cap2, ta, pa);

    int AA = doubleKnapsack(cap1, cap2, ta, pa);
    int OO = doubleKnapsack(cap1, cap2, to, po);

    printf("%d\r\n", (int) fmax(fmax(fmax(AO, OA), AA),OO));

    return 0;
}


int knapsack2(int cap, int * tab, int size){

    // initialisation of 2D array (first column to 1, rest 0)
    int fillable[cap + 1][size + 1];
    int capacity, object;
    for(capacity = 0 ; capacity <= cap ; capacity++) {
        for (object = 0 ; object <= size ; object++) fillable[capacity][object] = capacity == 0;
    }

    // calculation of fillable_matrix
    for(object = 1 ; object <= size ; object++) {
        for (capacity = 1 ; capacity <= cap ; capacity++) {
            if (capacity - tab[object - 1] < 0)
                fillable[capacity][object] = fillable[capacity][object-1];
            else
                fillable[capacity][object] = fillable[capacity][object-1] ||
                                             fillable[capacity - tab[object - 1]][object - 1];
            //printf("fillable[capacity %d][object %d] = %d\r\n", capacity, object, fillable[capacity][object]);
        }
    }

    int max = 0;
    for (capacity = 1 ; capacity <= cap ; capacity++) {
        if (fillable[capacity][size]) max = capacity;
    }

    return max;
}

int doubleKnapsack(int cap1, int cap2, int * tab, int size){

    // initialisation of 2D array (first column to 1, rest 0)
    /*int fillable[cap1 + 1][cap2+1][size + 1];
    int capacity1, capacity2, object;
    // on fill l'array avec des 0 sauf pour les capacites nulles
    for(capacity1 = 0 ; capacity1 <= cap1; capacity1++) {
        for(capacity2 = 0 ; capacity2 <= cap2; capacity2++) {
            for (object = 0 ; object <= size ; object++)
                fillable[capacity1][capacity2][object] = capacity1 == 0 || capacity2 == 0;
        }
    }

    // calculation of fillable_matrix
    for(object = 1 ; object <= size ; object++) {
        for (capacity1 = 1 ; capacity1 <= cap1 ; capacity1++) {
            for (capacity2 = 1 ; capacity2 <= cap2 ; capacity2++) {
                if (capacity1 - tab[object - 1] < 0) {
                    if (capacity2 - tab[object - 1] < 0) {
                        fillable[capacity1][capacity2][object] = fillable[capacity1][capacity2][object - 1];
                        printf("les deux\n");
                    }
                    else {
                        fillable[capacity1][capacity2][object] =
                                fillable[capacity1][capacity2 - tab[object - 1]][object] ||
                                fillable[capacity1][capacity2][object - 1];
                        printf("juste cap1\n");
                        //printf("fill: %d\n",fillable[capacity1][capacity2 - tab[object - 1]][object]);
                    }

                } else if (capacity2 - tab[object - 1] < 0){
                    fillable[capacity1][capacity2][object] =
                            fillable[capacity1 - tab[object - 1]][capacity2][object] ||
                            fillable[capacity1][capacity2][object - 1];
                    printf("juste cap2\n");
                } else {
                    fillable[capacity1][capacity2][object] =
                            fillable[capacity1 - tab[object - 1]][capacity2][object] ||
                            fillable[capacity1][capacity2 - tab[object - 1]][object] ||
                            fillable[capacity1][capacity2][object - 1];
                    printf("aucun\n");
                }
                //printf("fill[cap1 %d][cap2 %d][obj %d] = %d\r\n", capacity1, capacity2, object, fillable[capacity1][capacity2][object]);
            }
        }
    }

    int max = 0;
    for (capacity1 = 1 ; capacity1 <= cap1 ; capacity1++) {
        for (capacity2 = 1 ; capacity2 <= cap2 ; capacity2++) {
            if (fillable[capacity1][capacity2][size] && capacity1 + capacity2 > max) {
                max = capacity1 + capacity2;
                printf("cap 1: %d, cap 2: %d\n", capacity1, capacity2);
            }
        }
    }

    return max;*/

    int res[cap1 + 1][cap2+1];
    int capacity1, capacity2, object;

    for(capacity1 = 0 ; capacity1 <= cap1; capacity1++) {
        for(capacity2 = 0 ; capacity2 <= cap2; capacity2++)
            res[capacity1][capacity2] = 0 ;
    }

    for(object = 0 ; object < size ; object++) {
        for (capacity1 = cap1; capacity1 >= 0; capacity1--) {
            for (capacity2 = cap2; capacity2 >= 0; capacity2--) {
                if (capacity1 - tab[object] < 0){
                    if (capacity2 - tab[object] >= 0){
                        res[capacity1][capacity2] = fmax(
                                res[capacity1][capacity2],
                                res[capacity1][capacity2 - tab[object]] + tab[object]
                        );
                    }
                } else if (capacity1 - tab[object] < 0){
                    res[capacity1][capacity2] = fmax(
                            res[capacity1][capacity2],
                            res[capacity1 - tab[object - 1]][capacity2] + tab[object]
                    );
                } else {
                    res[capacity1][capacity2] = fmax(
                            res[capacity1][capacity2],
                            fmax(res[capacity1 - tab[object]][capacity2] + tab[object],
                                 res[capacity1][capacity2 - tab[object]] + tab[object])
                    );
                }
            }
        }
    }

    /*printf("printing array\n");
    for (int i = 0; i <= cap1; i++){
        for (int j = 0; j <= cap2; j++)
            printf("%d  ", res[i][j]);
        printf("\n");
    }*/

    return res[cap1][cap2];
}

/* Deux bateaux de pirates découvrent un trésor sur une ile déserte. Le trésor 
est composé d’objets en or et en argent, chaque objet ayant un certain poids. 
Chaque bateau peut transporter un certain poids maximal, en plus de la charge actuelle. 
Une contrainte supplémentaire : les restrictions de circulation des bateaux de 
pirates dans l’océan où se situe l’ile imposent un chargement d’un seul type d’article 
dans un bateau (dans notre cas : un bateau peut transporter un seul type de métal précieux).
Question : quelle est la quantité totale de métal du trésor (or et argent) 
transportable par les deux bateaux en une seule fois ? 

L'entrée standard sera composée d'une série de nombres entiers positifs séparés 
par des retours à la ligne :
- la capacité vacante du bateau 1 (entier n, 1 <= n <= 10000) ;
- la capacité vacante du bateau 2 (entier m, 1 <= m <= 10000) ;
- le nombre d’objets en argent du trésor (entier pa, 1 <= pa <= 100) ;
- le nombre d’objets en or du trésor (entier po, 1 <= po <= 100) ;
- pa+po nombres entiers positifs, représentants les poids des objets 
(les premiers pa en argent, les suivantes po en or)

Le format en entrée est respecté, vous n'avez pas à faire de test pour le vérifier. 

Format en sortie
----------------
La sortie : un nombre entier désignant la quantité totale en or et argent 
qui peut être transportée par les deux bateaux en une seule fois.
La ligne de sortie sera finalisée par un retour à la ligne de type "\r\n".

Exemple 1
-----------
Entrée :
10
12
3
3
5
2
4
8
7
5

Sortie :
21

Explication : 
 - Bateau 1 : les objets en argent de poids 5 et 4 ; 
 - Bateau 2 : les objets en or de poids 7 et 5




 12
 10
 3
 2
 7
 5
 10
 4
 5

 should return 10 + (7+5) = 22*/