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

node searchRecords(char *name) {
    node temp = root;
    while(temp){
        if(strcmp(name, temp->name) == 0) return temp;
        else if(strcmp(name, temp->name) < 0) temp = temp->leftChild;
        else temp = temp->rightChild; 
    }
    return NULL;
}


int main(void) {  

    char name[50];
    char num[11];

    int choice;
    
    while(1){
        printf("1. Insert record.\n");
        printf("2. Print records.\n");
        printf("3. Search records.\n");
        printf("4. Exit\n");

        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        switch(choice){
            case(1):
                printf("Enter name: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter number: ");
                fgets(num, 11, stdin);
                num[strcspn(num, "\n")] = 0;
                insertNode(name, num);
                break;
            case(2):
                printf("Printing records.\n");
                sortedPrint(root);
                break;
            case(3):
                printf("Enter name to search for: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                node temp = searchRecords(name); 
                if(temp) {
                    printf("Record found.\n");
                    printf("%s\n%s\n",temp->name, temp->number);
                } else printf("Record not found.\n");
                break;
            case(4):
                free(root);
                exit(1);
        }
    }
    return 0;
}