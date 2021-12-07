#include <stdbool.h>
#include "rotate.h"
#include "main.h"

extern node root;

node llRotate(node p) {
    node p_l = p->leftChild;
    node p_lr = p_l->rightChild;

    p_l->rightChild = p;
    p->leftChild = p_lr;
    p->height = height(p);
    p_l->height = height(p_l);

    if(root == p) root = p_l;
    return p_l;  
}

node lrRotate(node p) { 
    node p_l = p->leftChild;
    node p_lr = p_l->rightChild;

    p_l->rightChild = p_lr->leftChild;
    p->leftChild = p_lr->rightChild;

    p_lr->leftChild = p_l;
    p_lr->rightChild = p;

    p->height = height(p);
    p_l->height = height(p_l);
    p_lr->height = height(p_lr);

    if(root == p) 
        root = p_lr;
    return p_lr; 
}

node rrRotate(node p) {
    node p_r = p->rightChild;
    node p_rl = p_r->leftChild;

    p_r->leftChild = p;
    p->rightChild = p_rl;
    p->height = height(p);
    p_r->height = height(p_r);

    if(root == p) root = p_r;
    return p_r;  
}

node rlRotate(node p) {
    node p_r = p->rightChild;
    node p_rl = p_r->leftChild;

    p_r->rightChild = p_rl->rightChild;
    p->rightChild = p_rl->leftChild;

    p_rl->rightChild = p_r;
    p_rl->leftChild = p;
    p->height = height(p);
    p_r->height = height(p_r);
    p_rl->height = height(p_rl);

    if(root == p) root = p_rl;
    return p_rl; 
}