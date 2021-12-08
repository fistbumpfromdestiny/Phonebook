#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "tree.h"

extern node root;

static node createNode(){
    node temp = (node)malloc(sizeof(struct Node));
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

node insertNode(char *name, char *number, node p){
    // If root is NULL, create a new node and set it's
    // height to 1. 
    if(!p) { 
        node new = createNode();
        strcpy(new->name, name);
        strcpy(new->number, number);
        new->height = 1;
        return new;
    }

    if(strcmp(name, p->name) < 0) 
        p->leftChild = insertNode(name, number, p->leftChild);
    else if(strcmp(name, p->name) > 0)  
        p->rightChild = insertNode(name, number, p->rightChild);
    // Updates the height of every node during return time. 
    // p's height will be equal to the greatest height of either
    // left or right subtree.
    p->height = height(p);

    // A balance factor of > 1 means left side is unbalanced, 
    // whereas a factor of < -1 shows a right side imbalance.
    
    // If balance of p is 2 and p's left child is 1, tree's
    // unbalanced on the left side of subtree and has to be 
    // rotated left -> left.
    if(balance(p) == 2 && balance(p->leftChild) == 1)
        return llRotate(p);
    // Balance of p == 2 and p->leftChild = -1 means it's 
    // unbalanced on the right side of the left subtree, so 
    // we rotate left -> right.
    else if(balance(p) == 2 && balance(p->leftChild) == -1)
        return lrRotate(p);
    // Repeat balance checks, but for the right side of the tree.
    else if(balance(p) == -2 && balance(p->rightChild) == -1)
        return rrRotate(p);  
    else if(balance(p) == -2 && balance(p->rightChild) == -2)
        return rlRotate(p);   

    return p;
}

node deleteRecord(node p, char *name) {

    if(!p) return NULL;
    if(!p->leftChild && !p->rightChild) {
        if(p == root) root = NULL;
        free(p);
        return NULL;
    }   

    if (strcmp(name, p->name) < 0) p->leftChild = 
            deleteRecord(p->leftChild, name);
    else if (strcmp(name, p->name) > 0) p->rightChild = 
            deleteRecord(p->rightChild, name);
    // Compare the height between the two (eventual) subtrees and let 
    // either the Inorder predecessor (rightmost child of left subtree) 
    // or successor (leftmost child of right subtree) take the deleted 
    // nodes' place, to keep the tree balanced.
    else {
        node temp;
        if(calcHeight(p->leftChild) > calcHeight(p->rightChild)){
            temp = predecessor(p->leftChild);
            strcpy(p->name, temp->name);
            strcpy(p->number, temp->number);
            p->leftChild = deleteRecord(p->leftChild, temp->name);
        } else {
            temp = successor(p->rightChild);
            strcpy(p->name, temp->name);
            strcpy(p->number, temp->number);
            p->rightChild = deleteRecord(p->rightChild, temp->name);
        }
    }
    
    p->height = height(p);

    // Recalculate balance factor after deletion and rotate accordingly
    // if there is an imbalance.

    if(balance(p) == 2 && balance(p->leftChild) == 1)
        return llRotate(p);
    else if(balance(p) == 2 && balance(p->leftChild) == 0)
        return llRotate(p);
    else if(balance(p) == 2 && balance(p->leftChild) == -1)
        return lrRotate(p);
    else if(balance(p) == -2 && balance(p->rightChild) == 1)
        return rlRotate(p);  
    else if(balance(p) == -2 && balance(p->rightChild) == 0)
        return rrRotate(p);
    else if(balance(p) == -2 && balance(p->rightChild) == -1)
        return rrRotate(p);  
  
    return p;
}

void freeTree(node p){
    if(p) {
        freeTree(p->leftChild);
        freeTree(p->rightChild);
        free(p);
    }
}

static int calcHeight(node p) {
    // Move through subtrees till we hit null and 
    // count the height while returning.
    int left, right;
    if(!p) return 0;
    left = calcHeight(p->leftChild);
    right = calcHeight(p->rightChild);
    return (left > right) ? left + 1 : right + 1;
}

static int balance(node p) {
    // Returns the difference between height of left and
    // right subtree.
    int left, right;
    left = (p && p->leftChild) ? p->leftChild->height : 0;
    right = (p && p->rightChild) ? p->rightChild->height : 0;

    return left - right;
}

static node predecessor(node p) {
    // Returns the Inorder predecessor (the node which comes
    // after node p in an Inorder traversal).
    while(p && p->rightChild) p = p->rightChild;
    return p;
}

static node successor(node p) {
    // Returns the Inorder successor (the node which comes
    // before node p in an Inorder traversal).
    while(p && p->leftChild) p = p->leftChild;
    return p;
}

static int height(node p) {
    int left, right;
    // If p is not null and there is a child, set variable to 
    // height of p's child, otherwise set height to 0.
    left = p && p->leftChild ? p->leftChild->height : 0;
    right = p && p->rightChild ? p->rightChild->height : 0;
    // The node's height will be equal to the greater height
    // value, plus one.
    return left > right ? (left + 1) : (right + 1);
}
/* Left Left Rotation is done when there is an imbalance on the left 
subtree after a left->left insertion, or after a node deletion. 

Three nodes are rotated to the right: node p's left child takes the 
place of p. p moves one position to the right and the original right 
child of p's left child takes position as the left child of p.

Left Right Rotation is performed on a Left Right imbalance, which requires
a double rotation. 

Node p->left->right takes the place of p, p moves over one position to the 
right, and p's original left child stays where it is (now as the former 
p->left->right's left child).

We then perform a rotation of the children of former p->left->right where 
left and left->right rotates to p->left-right and p->left->right->right. 
The former p->left->right rotates to it's new p->right->left position. 

The same steps is taken for Right Right and Right Left rotation, but mirrored
to their Left Left and Left Right counterparts. */

static node llRotate(node p) {
   
    node p_l = p->leftChild;
    node p_lr = p_l->rightChild;

    p_l->rightChild = p;
    p->leftChild = p_lr;

    p->height = height(p);
    p_l->height = height(p_l);

    if(root == p) root = p_l;
    return p_l;  
}

static node lrRotate(node p) { 
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

static node rrRotate(node p) {
    node p_r = p->rightChild;
    node p_rl = p_r->leftChild;

    p_r->leftChild = p;
    p->rightChild = p_rl;

    p->height = height(p);
    p_r->height = height(p_r);

    if(root == p) root = p_r;
    return p_r;  
}

static node rlRotate(node p) {
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