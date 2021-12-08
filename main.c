#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "tree.h"
#include "io.h"

//typedef struct Node *node;
node root = NULL;
bool isRight = false;

int main(int argc, char **argv) {  
    
    char name[50];
    char num[11];
    node temp;

    if(argc > 1) {
        FILE *file;
        file = fopen(argv[1], "r");
        if(!file) {
            printf("Failed to open file \"%s\".\n", argv[1]);
            return -1;
        }
    
    while(!feof(file)) {
        fgets(name, sizeof(name), file);
        fgets(num, sizeof(num), file);
        if(name[0] != '\r' && name[0] != '\n'
        && num[0] != '\r' && num[0] != '\n')
        
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
                if(name[0] == '\r' || name[0] == '\n') break;
                printf("Enter number: ");
                fgets(num, 11, stdin);
                if(num[0] == '\r' || num[0] == '\n') break;
                num[strcspn(num, "\n")] = 0;
                root = insertNode(name, num, root);
                break;
            case(2):
                printf("Printing records.\n");
                printInorder(root);
                break;
            case(3):
                printf("Enter name to search for: ");
                fgets(name, 50, stdin);
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
                printTree("", root, isRight);
                break;
            case(6):
                freeTree(root);
                exit(1);
        }
    }
    return 0;
}