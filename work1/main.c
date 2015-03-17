#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "func.h"


/*
void checkingFile(FILE *fp, char *name){
    if(!(fp = fopen(name, "r"))){
        printf("cannot open file\n");
        exit(2);
    }
}
*/

int main(int argc, char *argv[])
{
    const char *word = argv[1];
    int array[argc - 2];

    if(argc < 3) {
        printf("You forgot to set word/fileNames!\n");
        exit(1);
    }
    for(int index = 0; index < argc - 2; index++){
        int temp = 0;
        int textCounter = 0;
        char ch;
        char *text = (char*)malloc(sizeof(char));

        FILE *file;
        if(!(file = fopen(argv[index + 2], "r"))){
            printf("Cannot open the #%i file\n", (index + 1));
            exit(2);
        }
        while((ch = fgetc(file)) != EOF){
            textCounter++;
            text = (char*)realloc(text, textCounter * sizeof(char));
            text[textCounter - 1] = ch;
        }
        fclose(file);
        temp = func(word, text, checkWord(word), (textCounter));
        free(text);
        array[index] = temp;
    }
    printf("Arithmetic Mean is %f\n",arithmeticMean(array, sizeof(array) / 4));
    return 0;
}
