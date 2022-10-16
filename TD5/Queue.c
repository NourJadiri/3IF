#include "Queue.h"

Queue* Init(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL; //pour que les pointeurs ne pointent pas n'importe ou... pas cool

    return queue;
}

void InsertValue(Queue* q , int val){
    Node* n = newNode(val);

    //si la queue est vide, le nouvel élément est en même temps front et rear
    if(q->rear == NULL){
        q->front = q->rear = n;

        //Ce return sert à arrêter la fonction à ce niveau si la condition est satisfaite, sans passer à la suite
        return;
    }

    //On met la nouvelle valeur au rear de la file et on change rear du coup
    q->rear->next = n;
    q->rear = n;

    //il se peut que y ait une confusion ici, mais il faut voir la liste un peu à l'envers.. comme ça genre
    /*
     * Node(N) <- Node(N-1) <- Node(N-2) <- ... Node(1)
     *
     * Quand il y a insertion, on insère juste avant Node(N) : Node(N+1) <- Node(N) ... Node(1)
     * Du coup Node(N).next devient Node(N+1) et ensuite on update le rear de la file
     */
}

int Dequeue(Queue* q){

    //si la queue est vide (donc pas de front), ne rien faire (il va return NULL)
    if(q->front == NULL) return 0;


    //le devant de la pile va bouger d'un Node (vu que le devant de la pile va se faire dégager)
    q->front = q->front->next;

    //si front devient NULL (plus d'élements dans la pile), alors on update rear aussi
    if(q->front == NULL) q->rear = NULL;

    return 1;

}

void Destroy(Queue* q){
    free(q->front);
    free(q->rear);
    free(q);
}