#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node{

    char name[50];
    char number[11];
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
        printf("Name: %sNumber: %s\n", p->name, p->number);
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

    if(strcmp(name, tail->name) < 0) 
        tail->leftChild = new;
    else tail->rightChild = new;
}

int calcHeight(node temp) {

    int leftHeight, rightHeight;
    if(!temp) return 0;
    calcHeight(temp->leftChild);
    calcHeight(temp->rightChild);
    if(leftHeight > rightHeight) return leftHeight + 1;
    else return rightHeight +1;
}

node predecessor(node temp) {

    while(temp && temp->rightChild) temp = temp->rightChild;
    return temp;
}

node successor(node temp) {

    while(temp && temp->leftChild) temp = temp->leftChild;
    return temp;
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

void printTree(char *prefix, node head, bool isLeft) {

    node temp = head;

    while(temp) {
    
        printf("%s", prefix);
        printf("%s", isLeft ? "|-" : "|_");
        printf("%s", temp->name);
        printTree(isLeft ? "   " : "|   ", temp->leftChild, true);
        printTree(isLeft ? "   " : "|   ", temp->rightChild, false);
        return;
    }

}

int main(int argc, char **argv) {  

    
    char name[50];
    char num[11];
    char *prefix = "";
    bool isLeft = false;
    
    node temp;

    if(argc > 1) {
        FILE *file;
        file = fopen(argv[1], "r");
        if(!file) {
            printf("Failed to open file \"%s\".\n", argv[1]);
            return -1;
        }
        char buf[2];
        while(!feof(file)) {
            fgets(name, sizeof(name), file);
            fgets(num, sizeof(num), file);
            if(name[0] != '\r' && name[0] != '\n'
            && num[0] != '\r' && num[0] != '\n')
            insertNode(name, num);

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
                temp = searchRecords(name); 
                if(temp) {
                    printf("Record found.\n");
                    printf("%s\n%s\n",temp->name, temp->number);
                } else printf("Record not found.\n");
                break;
            case(4):
                printf("Enter name to delete: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                root = deleteRecord(root, name); 
                break;
            case(5):
                printTree(prefix, root, isLeft);
                break;
            case(6):
                free(root);
                exit(1);
        }
    }
    return 0;
}