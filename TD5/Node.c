#include <stdio.h>
#include <malloc.h>
#include "Node.h"

Node* newNode(int val){
    Node* node;

    node  = (Node*)malloc(sizeof(Node));
    node->value = val;
    node->next = NULL;

    return node;
}