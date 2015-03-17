//func.c//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "func.h"

extern int rows;
extern int colums;
extern FILE *file;
void check(char ch){
    if(!(isdigit(ch) || ch == '.' || isspace(ch)
            || ch == '\n' || ch == '\t'))
    {
        printf("Check & change your file!\n");
        exit(1);
    }
}

double get_Elem(void *arra, int arrRow, int arrCol){
    double elem = 0;
    double **array = (double **)arra;
    elem = array[arrRow][arrCol];
    return elem;
}

void set_Elem(void *arra, int arrRows, int arrColumns){
    double **array = (double **)arra;
    char ch;
    char *temp;
    int index = 0, rowCounter = 0;
    int newArrRow = arrRows;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            printf("Empty column in matrix! Check file\n");
            exit(3);
        }
        check(ch);
        if(isdigit(ch)){
            index = 0;
            char *elem = (char *)malloc(sizeof(char));
            while(ch != EOF && ch != '\n'){
                check(ch);
                elem[index] = ch;
                ch = fgetc(file);
                index++;
                if(ch != '\n'){
                    elem = (char *)realloc(elem, index * sizeof(char));
                }
            }
            elem[index] = '\0'; //question!
            rowCounter++;
            temp = strtok(elem, " ");
            for(int j = 0; j < arrColumns; j++){
                if(temp == '\0'){
                    array[newArrRow-arrRows][j]= 0;
                }else{
                    array[newArrRow-arrRows][j]= atof(temp);
                    temp = strtok(NULL, " ");
                }
            }
            free(elem);
            arrRows--;
            if(newArrRow-arrRows == newArrRow) break;
        }
    }
    fclose(file);
}


void setSize(FILE *fp){
    char ch;
    int rowCounter = 0;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n'){
            printf("Empty column! Check file\n");
            exit(2);
        }
        check(ch);
        if(isdigit(ch)){
            int index = 0;
            char *elem = (char*)malloc(sizeof(char));
            while(ch != EOF && ch != '\n'){
                check(ch);
                elem[index] = ch;
                ch = fgetc(fp);
                index++;
                if(!(ch == '\n')){
                    elem = (char*)realloc(elem, index * sizeof(char));
                }
            }
            elem[index] = '\0'; //question!
            rowCounter++;
            if (rowCounter == 1){
                rows = atof(elem);
            }else if(rowCounter == 2){
                colums = atof(elem);
            }
            if(rowCounter == 2) break;
            free(elem);
        }
    }
}
