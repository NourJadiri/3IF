#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* mettez ici vos déclarations de fonctions et types */

typedef char * Key;

void error(void);

int main(void)
{
    int size;
    char lecture[100];
    char * key;
    char * val;

    if (fscanf(stdin,"%99s",lecture)!=1)
        error();
    while (strcmp(lecture,"bye")!=0)
    {
        if (strcmp(lecture,"init")==0)
        {
            if (fscanf(stdin,"%99s",lecture)!=1)
                error();
            size = atoi(lecture);
            /* mettre le code d'initialisation ici */
        }
        else if (strcmp(lecture,"insert")==0)
        {
            if (fscanf(stdin,"%99s",lecture)!=1)
                error();
            key = strdup(lecture);
            if (fscanf(stdin,"%99s",lecture)!=1)
                error();
            val = strdup(lecture);
            /* mettre ici le code d'insertion */
        }
        else if (strcmp(lecture,"delete")==0)
        {
            if (fscanf(stdin,"%99s",lecture)!=1)
                error();
            key = strdup(lecture);
            /* mettre ici le code de suppression */
        }
        else if (strcmp(lecture,"query")==0)
        {
            if (fscanf(stdin,"%99s",lecture)!=1)
                error();
            /* mettre ici le code de recherche et traitement/affichage du résultat */
        }
        else if (strcmp(lecture,"destroy")==0)
        {
            /* mettre ici le code de destruction */
        }
        else if (strcmp(lecture,"stats")==0)
        {
            /* mettre ici le code de statistiques */
        }

        if (fscanf(stdin,"%99s",lecture)!=1)
            error();
    }
    return 0;
}

/* fonction de décalage de bit circulaire */
unsigned int shift_rotate(unsigned int val, unsigned int n)
{
    n = n%(sizeof(unsigned int)*8);
    return (val<<n) | (val>> (sizeof(unsigned int)*8-n));
}

/* fonction d'encodage d'une chaîne de caractères */
unsigned int Encode(Key key)
{
    unsigned int i;
    unsigned int val = 0;
    unsigned int power = 0;
    for (i=0;i<strlen(key);i++)
    {
        val += shift_rotate(key[i],power*7);
        power++;
    }
    return val;
}

/* fonction de hachage simple qui prend le modulo */
unsigned int hash(unsigned int val, unsigned int size)
{
    return val%size;
}

/* fonction de hachage complète à utiliser */
unsigned int HashFunction(Key key, unsigned int size)
{
    return hash(Encode(key),size);
}

/* placer ici vos définitions (implémentations) de fonctions ou procédures */

void error(void)
{
    printf("input error\r\n");
    exit(0);
}