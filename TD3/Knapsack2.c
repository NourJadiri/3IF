#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(){
    int capacite;
    int i, j, k;

    int objets[101];

    scanf("%d" , &capacite);

    int lengthObjects = 0;
    do {
        scanf("%d",&objets[lengthObjects]);
    } while (objets[lengthObjects++] != -1);
    lengthObjects--;

    int sacs[capacite + 1];
    sacs[0] = TRUE;

    for(k = 1 ; k <= capacite ; k++) sacs[k] = 0;

    // IDEE ?
    //Somehow la le programme ne gère pas les cas ou tu peut ajouter un poids à un autre

    //---TO DO--- Trouver un moyen de faire ça

    for(i = 1 ; i <= capacite ; i++){
        for(j = 0 ; j < lengthObjects ; j++){
            if(i - objets[j] >= 0 && (sacs[i - objets[j]]) && objets[j] != -69) {
                sacs[i] = TRUE;
                objets[j] = -69;
            }
        }
        printf("sac[%d] : %d \n" ,i, sacs[i]);
    }
    printf("\n\r");
    if(sacs[capacite]) printf("OUI\r\n");
    else printf("NON\r\n");

    return 0; //on l'oublie pas celui la!!!!!!!
}