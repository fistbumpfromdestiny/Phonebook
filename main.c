#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char name[50];
    char number[11];
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
}*root = NULL;

typedef struct Node *node;

node createNode(){
    node temp = (node)malloc(sizeof(struct Node));
    temp->parent = temp->leftChild = temp->rightChild = NULL;
    return temp;
}


void sortedPrint(node p){
    
    if(p){
        sortedPrint(p->leftChild);
        printf("%s\n%s\n", p->name, p->number);
        sortedPrint(p->rightChild);     
    }
}


void insertNode(char *name, char *number){
    
    node temp = root;
    node tail, new;

    if(!root) { 
        new = createNode();
        strcpy(new->name, name);
        strcpy(new->number, number);
        root = new;
        return;
    }
    while (temp) {
        tail = temp;
        if(strcmp(name, temp->name) < 0) temp = temp->leftChild;
        else if(strcmp(name, temp->name) > 0) temp = temp->rightChild; 
        else return;
    }
    
    new = createNode();
    strcpy(new->name, name);
    strcpy(new->number, number);

    if(strcmp(name, tail->name) < 0) tail->leftChild = new;
    else tail->rightChild = new;
}


int main(void) {  

    char name[50];
    char num[11];

    
    insertNode("aaaa", "1080");
    insertNode("bbbb", "1080");
    insertNode("zzzz", "2080");
    insertNode("aaa", "3080");
    insertNode("kkkk", "4080");
   
    sortedPrint(root);
    printf("\n");
   
    return 0;
}