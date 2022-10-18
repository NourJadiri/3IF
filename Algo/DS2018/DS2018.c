#include <stdio.h>
#include <stdlib.h>

int moyenne(int * tab , int size);

int somme(int* tab, int size);

int moyenne(int* tab, int size);

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

    if(moyenne(rTab,r) > moyenne(nTab,n)) printf("R\n\r");
    else if(moyenne(rTab,r) < moyenne(nTab,n)) printf("N\n\r");

    else printf("RN\n\r");


    return 0;
}

int moyenne(int* tab , int size){

    return somme(tab,size)/size;
}

int somme(int* tab , int size){
    int s = 0;
    int i;
    for(i = 0 ; i < size ; i++){
        s += tab[i];
    }
    return s;
}

