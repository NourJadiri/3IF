#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int MAX_ITERATION = 69;

typedef struct{
    int n; // number of vertices in the graph
    int* nbSucc; // for each 0<=i<n, nbSucc[i] = number of successors of i
    int** succ; // for each 0<=i<n and each 0<=j<nbSucc[i], succ[i][j]=jth successor of i
} DIGRAPH;

typedef struct Node{
    double value;
    int index;
    struct Node* next;
}Node;

typedef struct{
    Node* first;
    int size;
}List;

void insertSorted ( List* l , double v, int i ){

    if (l->first == NULL)
    {
        l->first = (Node*)malloc(sizeof(Node));
        l->first->value = v;
        l->first->index = i;
        l->first->next = NULL;
        l->size++;
        return;
    }

    Node* insert = (Node*)malloc(sizeof(Node));
    insert->value = v;
    insert->index = i;
    insert->next = NULL;

    if ( v > l->first->value )
    {
        insert->next = l->first;
        l->first = insert;
        l->size++;
        return;
    }

    Node* iter = l->first;
    while (iter->next != NULL)
    {
        if ( v < iter->value && v > iter->next->value )
        {
            insert->next = iter->next;
            iter->next = insert;
            return;
        }
        l->size++;
        iter = iter->next;
    }
    if(iter->next == NULL)
    {
        iter->next = insert;
    }
}

double max_diff(double *v1, double *v2, int n) {
    double max = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = fabs(v1[i] - v2[i]);
        if (diff > max) {
            max = diff;
        }
    }
    return max;
}

double sum ( const double *arr , int n ){

    double s = 0;

    for (int i = 0 ; i < n ; i++){
        s+= arr[i];
    }

    return s;
}

void print_array(double *arr, int n, int iter) {
    printf("s%d = ( ", iter);
    for (int i = 0; i < n; i++) {
        printf("%.6f", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    //printf(" ) %.6f\n",sum(arr,n));
}

void copy_array(double *src, double *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
        src[i] = 0;
    }
}

DIGRAPH* readDigraph(FILE *fp){
    // return the DIGRAPH contained in file fp
    DIGRAPH *g = (DIGRAPH*)malloc(sizeof(DIGRAPH));
    if (fscanf(fp, "%d\n", &(g->n)) != 1 || g->n <= 0){
        printf("erreur de lecture du fichier\n");
        exit(1);
    }
    g->nbSucc = (int*)malloc(g->n*sizeof(int));
    g->succ = (int**)malloc(g->n*sizeof(int*));
    int succ[g->n];
    for (int i=0; i<g->n; i++){
        g->nbSucc[i] = 0;
        while (1){
            if (fscanf(fp, "%d", &(succ[g->nbSucc[i]])) != 1 || succ[g->nbSucc[i]] >= g->n){
                printf("erreur de lecture du fichier\n");
                exit(1);
            }
            if (succ[g->nbSucc[i]]<0) break;
            g->nbSucc[i]++;
        };
        g->succ[i] = (int*)malloc(g->nbSucc[i]*sizeof(int));
        memcpy(g->succ[i], succ, g->nbSucc[i]*sizeof(int));
    }
    return g;
}

void printDigraph(DIGRAPH *g){
    // For each vertex of g, display the list of its successors
    for (int i=0; i<g->n; i++){
        printf("Vertex %d has %d successors: ", i, g->nbSucc[i]);
        for (int j=0; j<g->nbSucc[i]; j++)
            printf("%d ", g->succ[i][j]);
        printf("\n");
    }
}

void pageRank (double *arr , int n)
{
    List * l = (List*)malloc(sizeof(List));
    l->first = NULL;

    for (int i = 0; i < n; ++i) {
        insertSorted(l, arr[i], i);
    }

    Node* iter = l->first;
    int i = 0;
    while( i < 5 )
    {
        printf("%d ", iter->index);
        iter = iter->next;
        i++;
    }

    free(l);
}

void calculScore ( DIGRAPH* g ){

    double s[g->n];
    double s_prev[g->n];

    // setting de s0
    for (int i = 0 ; i < g->n ; i++){
        s_prev[i] = 1.0/g->n;
        s[i] = 0;
    }
    // calcul des sommets absorbants

    int sommet_abs[g->n];
    int count =0;
    for (int i = 0; i < g->n; i++)
    {
        if(g->nbSucc[i]==0)
        {
            sommet_abs[count]=i;
            count++;
        }
    }
    
    // initialisation des paramètres
    double alpha = 0.9;
    double q = (1-alpha)/g->n;
    int iter = 1;
    double diff = 1;
    // update de s
    while (diff >= 1.0e-10 && iter < MAX_ITERATION)
    {
        double qabs = 0;
        for (int i = 0; i < count; i++)
        {
            qabs += alpha*s_prev[sommet_abs[i]]/g->n;
        }
        
        // iterer dans le vecteur s
        for (int i = 0; i < g->n; ++i)
        {
            // ajout de qabs à chaque s[i]
            s[i] += qabs + q;

            // parcourir les sommets
            for (int j = 0; j < g->nbSucc[i]; ++j) {
                int p = g->succ[i][j];
                s[p] += alpha*s_prev[i]/g->nbSucc[i];
            }
        }

        diff = max_diff(s_prev,s,g->n);
        print_array(s , g->n , iter);
        copy_array(s , s_prev , g->n);

        iter++;
    }

    pageRank(s_prev, g->n);

}



int main(){
    FILE* fp  = fopen("../S2/AIAA/TP1/assets/genetic.txt", "r");
    DIGRAPH* g = readDigraph(fp);
    fclose(fp);
    //printDigraph(g);

    calculScore(g);


    return 0;
}