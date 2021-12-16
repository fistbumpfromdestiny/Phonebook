#ifndef IO_H_
#define IO_H_
#include <stdbool.h>

struct Node * searchRecords(char *name, struct Node *root);
void printInorder(struct Node *p);
void printTree(char *indentation, struct Node *p, 
            struct Node *root, bool isRight);

#endif /* IO_H_ */