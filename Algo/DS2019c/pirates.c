#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display_array(int *tab , int size);


// AS : à supprimer

int main(){


    // Gestion des entrées
    int cap1 , cap2 , pa , po;

    printf("capacité libre bateau 1 :"); //AS
    scanf("%d" , &cap1);

    printf("Capacité libre bateau 2 :"); //AS
    scanf("%d",&cap2);

    printf("Nombre objets argent :"); //AS
    scanf("%d" , &pa);

    printf("Nombre objets or :"); //AS
    scanf("%d", &po);

    int *ta = (int*) malloc(pa * sizeof(int));
    int *to = (int*) malloc(po * sizeof(int));

    int i;
    for(i = 0 ; i < pa ; i++){
        printf("Objet argent %d :", i); //AS
        scanf("%d", &ta[i]);
    }

    for(i = 0 ; i < po ; i++){
        printf("Objet or %d :", i); //AS
        scanf("%d", &to[i]);
    }

    printf("Poids objets argent : "); //AS
    display_array(ta,pa); //AS

    printf("Poids objets or : "); //AS
    display_array(to,po); //AS
    //Fin d'entrée des données


    int AO = knapsack2(cap1, ta, pa) + knapsack2(cap2, to, po);
    int OA = knapsack2(cap1, to, po) + knapsack2(cap2, ta, pa);
    int AA = doubleKnapcksack(cap1, cap2, ta, pa);
    int OO = doubleKnapcksack(cap1, cap2, to, po);

    printf("%d\r\n", (int) fmax(fmax(fmax(AO, OA), AA),OO));

    return 0;
}

void display_array(int *tab , int size){
    for(int i = 0 ; i < size ; i++){
        printf("%d ",tab[i]);
    }
    printf("\n");
}

int knapsack2(int cap, int * tab, int size){


    return 0;
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
*/
