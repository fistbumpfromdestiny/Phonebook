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
static int height(struct Node *p);
static int calcHeight(struct Node *p);
static int balance(struct Node *p);
static struct Node * createNode();
static struct Node * predecessor(struct Node *p);
static struct Node * successor(struct Node *p);
static struct Node * llRotate(struct Node *p);
static struct Node * lrRotate(struct Node *p);
static struct Node * rlRotate(struct Node *p);
static struct Node * rrRotate(struct Node *p);
struct Node * deleteRecord(struct Node *p, char *name);
struct Node * insertNode(char *name, char *number,
                        struct Node *p);

#endif  /* TREE_H_ */