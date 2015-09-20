#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node{
    char *data;
    struct Node *left, *right;
};

typedef struct Node *PNode;

int check(char *x);
void cleanTree(PNode *Tree);
void addToTree(PNode *Tree, char *x);
void Print(PNode Tree, char *x);

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    FILE *file;
    FILE *file2;
    PNode Head = NULL;
    size_t count;
    char *mes;
    int ch;
    int index = 0;
    int counter = 0;

    if(!(file = fopen(argv[1], "r"))){
        printf("Cannot open the #%i file\n", 1);
        exit(1);
    }
    if(!(file2 = fopen(argv[2], "wb"))){
        printf("Cannot open the #%i file\n", 2);
        exit(2);
    }

    while((ch = fgetc(file)) != EOF){
        index = 0;
        counter++;
        if(!isspace(ch) || fgetc(file) != EOF){
            counter++;
            char *text = (char*)malloc(sizeof(char));
            while(!isspace(ch)){
                text[index] = ch;
                index++;
                ch = fgetc(file);
                if(!isspace(ch)){
                    counter++;
                    text = (char*)realloc(text, index * sizeof(char));
                }
            }
            text[index] = '\0';
            addToTree(&Head, text);
            free(text);
        }
    }
    mes = (char *)malloc(counter * sizeof(char));
    Print(Head, mes);
    count = fwrite(mes,strlen(mes), 1, file2);
    if(count != 1){
        printf("problem\n");
    }
    free(mes);
    cleanTree(&Head);
    free(Head->data);
    Head = NULL;

    printf("Bye!\n");
    return 0;
}

int check(char *x){
    int index = 0;
    while(x[index] == '\0'){
        index ++;
    }
    return index;
}

void cleanTree(PNode *Tree){
    if(!(*Tree)) return;
    if((*Tree)->left != NULL){
        cleanTree(&(*Tree)->left);
        //free(((*Tree)->left)->data);
        (*Tree)->left = NULL;
        cleanTree(&(*Tree)->right);
        (*Tree)->right = NULL;
        //free(((*Tree)->right)->data);
        return;
    }
}

void addToTree(PNode *Tree, char *x){
    if (!(*Tree)){
        (*Tree) = (PNode)malloc(sizeof(struct Node));
        (*Tree)->data = (char*)realloc((*Tree)->data, strlen(x)*sizeof(char));
        strcpy((*Tree)->data, x);
        (*Tree)->right = NULL;
        (*Tree)->left = NULL;
        return;
    }
    if (strcmp(x,(*Tree)->data) <= 0){
        addToTree(&(*Tree)->left, x);
    }
    else {
        addToTree(&(*Tree)->right, x);
    }
}
void Print(PNode Tree, char *x){
    char space[] = " ";
    if (!Tree)return;
    Print(Tree->left, x);
    strcat(x, Tree->data);
    strcat(x, space);
    Print(Tree->right, x);
}

