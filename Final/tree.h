#ifndef TREE_H_
#define TREE_H_
#include "main.h"

struct Node{
    char name[NAME_LENGTH];
    char number[NUM_LENGTH];
    int height;
    struct Node *leftChild;
    struct Node *rightChild;
};

typedef struct Node *node;

struct Node * createNode();
struct Node * llRotate(struct Node *p);
struct Node * lrRotate(struct Node *p);
struct Node * rlRotate(struct Node *p);
struct Node * rrRotate(struct Node *p);
struct Node * predecessor(struct Node *p);
struct Node * successor(struct Node *p);
struct Node * deleteRecord(struct Node *p, char *name);
struct Node * insertNode(char *name, char *number,
                        struct Node *p);
void freeTree(struct Node *p);
int height(struct Node *p);
int calcHeight(struct Node *p);
int balance(struct Node *p);

#endif  /* TREE_H_ */