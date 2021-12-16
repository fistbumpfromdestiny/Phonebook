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

void freeTree(struct Node *p);

struct Node * deleteRecord(struct Node *root, struct Node *p, char *name);
struct Node * insertNode(char *name, char *number,
                        struct Node *p, struct Node *root);

#endif  /* TREE_H_ */