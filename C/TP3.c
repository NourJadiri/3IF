#include <stdlib.h>
#include <stdio.h>

typedef struct _elem{
    int value;
    struct _elem* next;
} elem;

//initialisation: liste vide
elem* list = NULL;

void afficher(){
    if (list == NULL) printf("la liste est vide\r\n");
    else {
        printf("affichage de la liste:\r\n");
        elem *actuel = list;
        while (actuel != NULL){
            printf("%d\r\n", (*actuel).value);
            actuel = (*actuel).next;
        }
        printf("fin de la liste\r\n");
    }
}

void ajouter_en_tete(){
    printf("entrez un nombre\r\n");
    int n;
    scanf("%d", &n);

    elem *e = malloc(sizeof(elem));
    (*e).next = list;
    (*e).value = n;
    list = e;
}

void rechercher(){
    printf("entrez le nombre a chercher\r\n");
    int nombre;
    scanf("%d", &nombre);

    elem *actuel = list;
    int found = 0;
    int position = 0;

    while (actuel != NULL){
        if ((*actuel).value == nombre) {
            printf("trouvé à la position %d\r\n", position+1);
            found++;
        }
        actuel = (*actuel).next;
        position++;
    }
    if (found==0) printf("pas trouvé :(\r\n");
    else printf("le nombre apparait %d fois\r\n", found);
}

void ajouter_en_queue(){
    printf("entrez un nombre\r\n");
    int n;
    scanf("%d", &n);

    elem *actuel = list;
    elem *nv = malloc(sizeof(elem));

    if (list == NULL) {
        (*nv).value = n;
        list = nv;
    } else {
        while ((*actuel).next != NULL) { //on s'arrete avant le dernier
            actuel = (*actuel).next;
        }
        (*actuel).next = nv;
        (*nv).value = n;
    }
}

void supprimer(){
    if (list == NULL) printf("la liste est deja vide\r\n");
    else {
        printf("entrez le nombre a supprimer\r\n");
        int n;
        scanf("%d", &n);
        elem *actual;

        int found = 0;

        while (list != NULL && list->value == n) {
            found = 1;
            actual = list->next;
            free(list);
            list = actual;
        }

        actual = list;
        elem *next;

        while (actual != NULL && actual->next != NULL){
            next = actual->next;

            if(next->value == n){
                found = 1;
                actual->next = next->next;
                free(next);
                next = actual->next;
            } else {
                actual = next;
                next = next->next;
            }
        }
        if (found == 0) printf("ce nombre n'est pas dans la liste\r\n");
    }
}

void dupliquer(){
    if (list == NULL) printf("la liste est vide\r\n");
    else {
        printf("entrez le nombre à dupliquer\r\n");
        int n;
        scanf("%d", &n);

        elem *actual = list;

        int found = 0;

        while (actual != NULL) {
            if ((*actual).value == n) {
                elem *aj = malloc(sizeof(elem));
                (*aj).value = n;
                (*aj).next = (*actual).next;
                (*actual).next = aj;
                actual = aj->next;
                found = 1;
            } else actual = actual->next;
        }
        if (found == 0) printf("ce nombre n'est pas dans la liste\r\n");
    }
}

void sorted(){
    if (list == NULL) printf("la liste est vide\r\n");
    else {
        elem *actual = list;
        int yesOrNo = 1;
        while (actual->next != NULL) {
            if ((actual->next)->value < actual->value){
                yesOrNo = 0;
                break;
            }
            actual = actual->next;
        }
        if (yesOrNo==0) printf("no\r\n");
        else printf("yes\r\n");
    }
}

void ajouter_en_place(){
    printf("entrez le nombre à ajouter\r\n");
    int n;
    scanf("%d", &n);

    elem *nv = malloc(sizeof(elem));
    (*nv).value = n;

    elem *actual = list;
    int placed = 0;

    if (list == NULL || actual->value >= n) {
        nv->next = actual;
        list = nv;
    } else {
        while (actual->next != NULL) {
            if (actual->value <= n && n <= (actual->next)->value) {
                (*nv).next = actual->next;
                actual->next = nv;
                placed = 1;
                break;
            }
            actual = actual->next;
        }
        if (!placed) {
            actual->next = nv;
        }
    }
}

void retourner() {
    if (list == NULL) printf("la liste est vide\r\n");
    else {
        elem *actual = list;
        elem *previous = NULL;
        elem *next;
        while (actual != NULL) {
            next = actual->next;
            actual->next = previous;
            previous = actual;
            actual = next;
        }
        list = previous;
    }
}


int main () {
    while (1) {
        printf("menu: \n");
        printf("\t1: afficher la liste\n");
        printf("\t2: ajouter en tete\n");
        printf("\t3: ajouter en queue\n");
        printf("\t4: ajouter un nombre\n");
        printf("\t5: rechercher dans la liste\n");
        printf("\t6: dupliquer dans la liste\n");
        printf("\t7: supprimer dans la liste\n");
        printf("\t8: verifier si la liste est triee\n");
        printf("\t9: inverser la liste\n");
        printf("\t0: quitter\n");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                goto fin;
            case 1:
                afficher();
                break;
            case 2:
                ajouter_en_tete();
                break;
            case 3:
                ajouter_en_queue();
                break;
            case 4:
                ajouter_en_place();
                break;
            case 5:
                rechercher();
                break;
            case 6:
                dupliquer();
                break;
            case 7:
                supprimer();
                break;
            case 8:
                sorted();
                break;
            case 9:
                retourner();
                break;
            default:
                printf("choix incorrect\n");
                continue; //revenir au menu
        }
    }
    fin:
    printf("see you :)\n");

    return 0;
}

