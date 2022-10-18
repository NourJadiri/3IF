#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* mettez ici vos déclarations de fonctions et types */

/* etat d'une case (peut aussi etre fait avec un enum) */
#define EMPTY 0
#define SET 1
#define REMOVED 2

/* utile pour affichage */
const char * Labels[] = {"Empty", "Set", "Removed"};

/* raccourcis vers types cle et valeur */
typedef char * Key;
typedef char * Value;

/* une cellule de la table */
typedef struct {
    Key key;
    unsigned char status;
    Value val;
} Data;

/* la table de hachage elle-même */
typedef struct {
    Data * tab;
    int size;
} HashTable;


HashTable * Init(unsigned int size);

void Insert(HashTable * aHashTable, Key aKey, Value aVal);

void Delete(HashTable * aHashTable, Key aKey);

void Query(HashTable * aHashTable, Key aKey);

void Stats(HashTable * aHashTable);

void Destroy(HashTable * aHashTable);

void error(void);


int main(void)
{
    int size;
    char lecture[100];
    char * key;
    char * val;

    HashTable * aHashTable;

    if (fscanf(stdin, "%99s", lecture) != 1)
        error();
    while (strcmp(lecture, "bye") != 0)
    {
        if (strcmp(lecture, "init") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            size = atoi(lecture);
            /* mettre le code d'initialisation ici */
            aHashTable = Init(size);
        }
        else if (strcmp(lecture, "insert") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            key = strdup(lecture);
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            val = strdup(lecture);
            /* mettre ici le code d'insertion */
            Insert(aHashTable, key, val);
        }
        else if (strcmp(lecture, "delete") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            key = strdup(lecture);
            /* mettre ici le code de suppression */
            Delete(aHashTable, key);
        }
        else if (strcmp(lecture, "query") == 0)
        {
            if (fscanf(stdin, "%99s", lecture) != 1)
                error();
            key = strdup(lecture);
            /* mettre ici le code de recherche et traitement/affichage du résultat */
            Query(aHashTable, key);
        }
        else if (strcmp(lecture, "destroy") == 0)
        {
            /* mettre ici le code de destruction */
            Destroy(aHashTable);
        }
        else if (strcmp(lecture, "stats") == 0)
        {
            /* mettre ici le code de statistiques */
            Stats(aHashTable);
        }

        if (fscanf(stdin, "%99s", lecture) != 1)
            error();
    }
    return 0;
}

/* fonction de décalage de bit circulaire */
unsigned int shift_rotate(unsigned int val, unsigned int n)
{
    n = n % (sizeof(unsigned int) * 8);
    return (val << n) | (val >> (sizeof(unsigned int) * 8 - n));
}

/* fonction d'encodage d'une chaîne de caractères */
unsigned int Encode(Key key)
{
    unsigned int i;
    unsigned int val = 0;
    unsigned int power = 0;
    for (i = 0; i < strlen(key); i++)
    {
        val += shift_rotate(key[i],power * 7);
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
    return hash(Encode(key), size);
}

/* placer ici vos définitions (implémentations) de fonctions ou procédures */

/* initialisation de la hashTable */
HashTable * Init(unsigned int size)
{
    HashTable * aHashTable = (HashTable*) malloc(sizeof(HashTable));
    aHashTable->size = size;
    aHashTable->tab = (Data*) malloc(sizeof(Data) * size);

    int i = 0;
    for (i = 0; i < size; i++)
    {
        aHashTable->tab[i].status = EMPTY;
        //jsp si cest necessaire ca mais dans le doute lets do it
        aHashTable->tab[i].key = "";
        aHashTable->tab[i].val = "";
    }
    return aHashTable;
}

/* insertion dans la HT */
void Insert(HashTable * aHashTable, Key aKey, Value aVal)
{
    // on check si cle presente dans HT
    int i = HashFunction(aKey, aHashTable->size);
    //printf("i: %d\r\n", i);
    int firstIndex = i;
    do
    {
        // cle deja presente => ecrase valeur associee
        if (strcmp(aHashTable->tab[i].key, aKey) == 0)
        {
            aHashTable->tab[i].val = aVal;
            return;
        }
        i++;
        i %= aHashTable->size;
    } while (aHashTable->tab[i].status != EMPTY && i != firstIndex);

    // cle non presente => on la rajoute premiere place dispo
    i = firstIndex;
    do {i = (i+1) % aHashTable->size; }
    while (aHashTable->tab[i].status == SET && i != firstIndex);
    if (i != firstIndex)
    {
        aHashTable->tab[i].val = aVal;
        aHashTable->tab[i].status = SET;
        aHashTable->tab[i].key = aKey;
    }
}

/* suppression dans la HT */
void Delete(HashTable * aHashTable, Key aKey)
{
    int i = HashFunction(aKey, aHashTable->size);
    int firstIndex = i;
    do
    {
        if (strcmp(aHashTable->tab[i].key, aKey) == 0)
        {
            aHashTable->tab[i].val = "";
            aHashTable->tab[i].key = "";
            aHashTable->tab[i].status = REMOVED;
            return;
        }
        i = (i+1) % aHashTable->size;
    } while (aHashTable->tab[i].status != EMPTY && i != firstIndex);
}

/* requete dans la HT *
 * returns 1 si aKey existe et a une val associee*
 * returns 0 si aKey n'est pas dans la HT */
void Query(HashTable * aHashTable, Key aKey)
{
    int i = HashFunction(aKey, aHashTable->size);
    int firstIndex = i;
    do
    {
        if (strcmp(aHashTable->tab[i].key, aKey) == 0)
        {
            printf("%s\r\n", aHashTable->tab[i].val);
            return;
        }
        i = (i+1) % aHashTable->size;
    } while (aHashTable->tab[i].status != EMPTY && i != firstIndex);

    printf("Not found\r\n");
}

/* stats de la HT */
void Stats(HashTable * aHashTable)
{
    int empty = 0;
    int deleted = 0;
    int used = 0;

    int i;
    for (i = 0; i < aHashTable->size; i++)
    {
        if (aHashTable->tab[i].status == EMPTY)
            empty++;
        else if (aHashTable->tab[i].status == REMOVED)
            deleted++;
        else if (aHashTable->tab[i].status == SET)
            used++;
    }
    printf("size    : %d\r\n", aHashTable->size);
    printf("empty   : %d\r\n", empty);
    printf("deleted : %d\r\n", deleted);
    printf("used    : %d\r\n", used);
}

/* liberation de la HT */
void Destroy(HashTable * aHashTable)
{
    int i;
    for (i = 0; i < aHashTable->size; i++)
    {
        if (aHashTable->tab[i].status == SET)
        {
            free(aHashTable->tab[i].key);
            free(aHashTable->tab[i].val);
        }
    }
    free(aHashTable->tab);
    free(aHashTable);
}

void error(void)
{
    printf("input error\r\n");
    exit(0);
}