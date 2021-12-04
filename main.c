#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedList{
    char name[50];
    char number[10];
    struct linkedList *parent;
    struct linkedList *leftChild;
    struct linkedList *rightChild;
};

typedef struct linkedList *node;

node createNode(){
    node temp;
    temp = (node)malloc(sizeof(struct linkedList));
    temp->parent = NULL;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}

void searchTree(node head, char *name){


}

node addNode(char *name, char *number, node head){
    node temp, p;

    temp = createNode();
    for(int i = 0; i < strlen(name); i++)
        temp->name[i] = name[i];
    for(int i = 0; i < strlen(number); i++)
        temp->number[i] = number[i];
    

    if(!head){
        head = temp;
    }else{
        p = head;
        while(p->next){
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

int main(void) {

    return 0;
}