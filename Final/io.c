#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "io.h"

extern node root;
extern bool isRight;

void printInorder(node p){ 
    if(p){
        printInorder(p->leftChild);
        printf("Name: %sNumber: %s\n\n", 
            p->name, p->number);
        printInorder(p->rightChild);     
    }
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