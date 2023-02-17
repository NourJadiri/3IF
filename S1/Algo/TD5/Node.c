#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

Node* newNode(int val){
    Node* node;

    node  = (Node*)malloc(sizeof(Node));
    node->value = val;
    node->next = NULL;

    return node;
}