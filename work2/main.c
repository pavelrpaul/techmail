#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "func.h"

int rows;
int colums;
FILE *file;
int main(int argc, char *argv[])
{
    int max = 0;
    if(!(file = fopen(argv[1], "r"))){
        printf("Cannot open the #%i file\n", 1);
        exit(1);
    }
    setSize(file);
    double **array = (double **)malloc(rows * sizeof(double *));
    for(int i = 0; i < rows; i ++){
        array[i] = (double *)malloc(colums * sizeof(double));
    }
    set_Elem((void *)array, rows, colums);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colums; j++){
            printf("%f ",array[i][j]);
        }
        printf("\n");
    }

    double maxNorm[rows];
    for(int i = 0; i < sizeof(maxNorm)/sizeof(double); i++){
        for(int j = 0; j < colums; j++){
            maxNorm[i] += get_Elem((void *)array, i, j);
        }
    }
    for(int i = 0; i < sizeof(maxNorm)/sizeof(double); i++){
       if(max < maxNorm[i]) max = maxNorm[i];
    }
    printf("%i\n", max);
    return 0;
}

