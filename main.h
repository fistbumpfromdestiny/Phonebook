#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Node{
    char name[50];
    char number[11];
    int height;
    struct Node *leftChild;
    struct Node *rightChild;
};

struct Node * createNode();
void sortedPrint(struct Node *p);
int height(struct Node *p);

struct Node * insertNode(char *name, char *number,
                        struct Node *p);
int calcHeight(struct Node *p);
int balance(struct Node *p);
struct Node * predecessor(struct Node *p);
struct Node * successor(struct Node *p);
struct Node * deleteRecord(struct Node *p, char *name);
struct Node * searchRecord(char *name);
void printTree(char *indentation, struct Node *p, 
                bool isRight);

#endif /* MAIN_H_ */
