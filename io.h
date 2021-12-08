#ifndef IO_H_
#define IO_H_
#include <stdbool.h>

struct Node * searchRecords(char *name);
void printInorder(struct Node *p);
void printTree(char *indentation, struct Node *p, 
                bool isRight);

#endif /* IO_H_ */