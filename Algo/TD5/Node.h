//
// Created by Nour on 16/10/2022.
//

#ifndef INC_3IF_NODE_H
#define INC_3IF_NODE_H

typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* newNode(int val);

#endif //INC_3IF_NODE_H
