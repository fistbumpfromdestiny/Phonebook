#ifndef ROTATE_H_
#define ROTATE_H_
#include "main.h"

typedef struct Node *node;

struct Node * llRotate(struct Node *p);
struct Node * lrRotate(struct Node *p);
struct Node * rlRotate(struct Node *p);
struct Node * rrRotate(struct Node *p);

#endif  /* ROTATE_H_ */