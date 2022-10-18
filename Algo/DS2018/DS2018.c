#include <stdio.h>
#include <stdlib.h>

int somme(int* tab, int size);

double moyenne(int* tab, int size);

int main(){

    int r,n;
    scanf("%d",&r);
    scanf("%d",&n);

    int* rTab = (int*)malloc(r*sizeof(int));
    int* nTab = (int*)malloc(n*sizeof(int));

    int i;
    for(i = 0; i < r ; i++){
        scanf("%d",&rTab[i]);
    }

    for(i = 0; i < n ; i++){
        scanf("%d",&nTab[i]);
    }

    //LES \r\n CA SE MET DANS CET ORDRE LA ET PAS L'INVERSE!!!!!!
    if(moyenne(rTab,r) > moyenne(nTab,n)) printf("R\r\n");
    else if(moyenne(rTab,r) < moyenne(nTab,n)) printf("N\r\n");

    else printf("RN\r\n");

    return 0;
}

double moyenne(int* tab , int size){
    return ((double)(somme(tab,size))/(double)(size));
}

int somme(int* tab , int size){
    int s = 0;
    int i;
    for(i = 0 ; i < size ; i++){
        s += tab[i];
    }
    return s;
}
/* VOICI UNE AUTRE SOLUTION
 * (PCQ NOUR SE COMPLIQUE BCP TROP LA VIE ET QUON EST DES FLEMMARDS)
 * ((ET QUE MALLOC + FREE CA FAIT CHIER))
 *

#include <stdio.h>

int main() {
    int n, m, sum_n=0, sum_m=0, temp_n, temp_m;
    scanf("%d", &n);
    scanf("%d", &m);

    //calcul de la somme des poids
    int i, j;
    for (i = 0; i<n; i++){
        scanf("%d", &temp_n);
        sum_n += temp_n;
    }
    for (j = 0; j<m; j++){
        scanf("%d", &temp_m);
        sum_m += temp_m;
    }

    //calcul de la moyenne des poids
    double avg_n, avg_m;
    avg_n = (double)(sum_n)/(double)(n);
    avg_m = (double)(sum_m)/(double)(m);

    //printing
    if (avg_n > avg_m) printf("R\r\n");
    else if (avg_n < avg_m) printf("N\r\n");
    else if (avg_n == avg_m) printf("RN\r\n");

    return 0;
}*/