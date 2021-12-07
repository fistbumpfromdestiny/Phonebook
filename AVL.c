#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

struct Node{
    char name[50];
    char number[11];
    int height;
    struct Node *leftChild;
    struct Node *rightChild;
}*root = NULL;

typedef struct Node *node;

node createNode(){

    node temp = (node)malloc(sizeof(struct Node));
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

void sortedPrint(node p){

    if(p){
        sortedPrint(p->leftChild);
        printf("Name: %sNumber: %s Height: %d\n", 
            p->name, p->number, p->height);
        sortedPrint(p->rightChild);     
    }
}

int height(node p) {
    int left, right;
    // If p is not null and there is a child, set variable to 
    // height of p's child, otherwise set height to 0.
    left = p && p->leftChild ? p->leftChild->height : 0;
    right = p && p->rightChild ? p->rightChild->height : 0;
    // The node's height will be equal to the greater height
    // value, plus one.
    return left > right ? (left + 1) : (right + 1);
}

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
    node right = p-> rightChild;
    node rightleft = right->leftChild;

    right->rightChild = rightleft->rightChild;
    p->rightChild = rightleft->leftChild;

    rightleft->rightChild = right;
    rightleft->leftChild = p;
    p->height = height(p);
    right->height = height(right);
    rightleft->height = height(rightleft);

    if(root == p) 
        root = rightleft;
    return rightleft;
    }

node insertNode(char *name, char *number, node p){
    
    node new = NULL;

    if(!p) { 
        new = createNode();
        strcpy(new->name, name);
        strcpy(new->number, number);
        new->height = 1;
        return new;
    }

    if(strcmp(name, p->name) < 0) 
        p->leftChild = insertNode(name, number, p->leftChild);
    else if(strcmp(name, p->name) > 0)  
        p->rightChild = insertNode(name, number, p->rightChild);
    // Updates the height of every node during returning time. 
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

int calcHeight(node p) {

    int left, right;
    if(!p) return 0;
    left = calcHeight(p->leftChild);
    right = calcHeight(p->rightChild);
    return (left > right) ? left + 1 : right + 1;
}

int balance(node p) {
    // Returns the difference between height of left and
    // right subtree.
    int left, right;
    left = (p && p->leftChild) ? p->leftChild->height : 0;
    right = (p && p->rightChild) ? p->rightChild->height : 0;

    return left - right;

}

node predecessor(node p) {

    while(p && p->rightChild) p = p->rightChild;
    return p;
}

node successor(node p) {

    while(p && p->leftChild) p = p->leftChild;
    return p;
}

node deleteRecord(node p, char *name) {

    node temp;

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
    else {
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
    return p;
}

node searchRecords(char *name) {

    node temp = root;
    
    while(temp){
        if(strcmp(name, temp->name) == 0) return temp;
        else if(strcmp(name, temp->name) < 0) temp = temp->leftChild;   
        else temp = temp->rightChild; 
    }
    return NULL;
}

void printTree(char *indentation, node p, bool isRight) {

    if(!p) {
        printf("%s", indentation);
        printf("└── *\n");
        return;
    }
    char *newindent = (char*) malloc(256 * sizeof(char));
    
    printf("%s", indentation);
    if(p == root) printf("└ %s", p->name);
    else printf("└── %s", p->name);
    
    // Concatenates indentation and result of ternary operation into 
    // newstring
    sprintf(newindent, "%s%s", indentation, (isRight ? "│  " : " "));
    printTree(newindent, p->rightChild, true);
    printTree(newindent, p->leftChild, false);
   
    free(newindent);
    }

int main(int argc, char **argv) {  

    
    char name[50];
    char num[11];
    
    bool isLeft = false;
    
    node temp;

    if(argc > 1) {
        FILE *file;
        file = fopen(argv[1], "r");
        if(!file) {
            printf("Failed to open file \"%s\".\n", argv[1]);
            return -1;
        }
    
        while(fgets(name, sizeof(name), file) != NULL){
              fgets(num, sizeof(num), file);
              root = insertNode(name, num, root);
        }
        fclose(file);   
    }

    int choice;
    
    while(1){
        printf("\n");
        printf("1. Insert record.\n");
        printf("2. Print records.\n");
        printf("3. Search records.\n");
        printf("4. Delete records.\n");
        printf("5. Print tree.\n");
        printf("6. Exit\n");

        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        switch(choice){
            case(1):
                printf("Enter name: ");
                fgets(name, 50, stdin);
                printf("Enter number: ");
                fgets(num, 11, stdin);
                num[strcspn(num, "\n")] = 0;
                root = insertNode(name, num, root);
                break;
            case(2):
                printf("Printing records.\n");
                sortedPrint(root);
                break;
            case(3):
                printf("Enter name to search for: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                temp = searchRecords(name); 
                if(temp) {
                    printf("Record found.\n");
                    printf("%s\n%s\n",temp->name, temp->number);
                } else printf("Record not found.\n");
                break;
            case(4):
                printf("Enter name to delete: ");
                fgets(name, 50, stdin);
                root = deleteRecord(root, name); 
                break;
            case(5):
                printTree("", root, isLeft);
                break;
            case(6):
                free(root);
                exit(1);
        }
    }
    return 0;
}