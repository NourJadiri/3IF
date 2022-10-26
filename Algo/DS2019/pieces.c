#include <stdio.h>
#include <stdlib.h>

int min(int a , int b){
    return a<=b ? a: b;
}

int main(){

    int nb_billets , somme_a_rendre ;

    scanf("%d",&nb_billets);

    int *billets = (int*)malloc(nb_billets*sizeof(int));

    int i,j;
    for (i = 0; i < nb_billets; i++)
        scanf("%d", &billets[i]);


    scanf("%d",&somme_a_rendre);

    int *DP = (int*)malloc(sizeof(int) * (somme_a_rendre+1));


    DP[0] = 0;
    int nb_billet_min;

    for(i = 1 ; i <= somme_a_rendre ; i++){
        nb_billet_min = 999999; //je set le nombre optimal de billets sur le nombre max possible (somme_à_rendre si je n'avais que des billets de 1).

        for(j = 0 ; j < nb_billets ; j++){
            /*
             * On itère dans le tableau en vérifiant à chaque fois si combien de billets je dois rendre à DP[i - billets[j]]
             * On rajoute 1 au nombre de billets rendus
             * puis on prend le minimum de toutes ces valeurs.
             */
            if(i - billets[j] >= 0){
                nb_billet_min = min(nb_billet_min,DP[i - billets[j]] + 1);
            }
        }

        DP[i] = nb_billet_min;
    }

    printf("%d\r\n",DP[somme_a_rendre]);


    return 0;
}

/*Soit un système de monnaie S, défini par les types de billet de valeur b1, b2, …, bn,
avec b1, b2, …, bn des entiers positifs. L’objectif est de rendre une somme N (nombre
entier positif) de façon optimale, c'est-à-dire avec le nombre minimal de billets.*/


