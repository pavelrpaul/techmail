//func.c//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "func.h"

int func(const char *word, const char *text, int sizeOfword, int sizeOftext){ //word parser
    int index;
    int count = 0;
    for (int i = 0, j = 0; i < sizeOftext; i++){
        j = 0; //i - mean word index in text
        index = 0; // how mane letters were the same as in our WORD
        if (i == 0 && text[i + j] == word[j]) {  // begin from firs word AND with first equal letter
            while (text[i + j] == word[j] && j != (sizeOfword - 1)) { // while word int text and WORD the same AND j < word last letter
                j++;
                index++;
            }
            if (!(index % (sizeOfword - 1))) { // if index = last word index => +1 WORD
                count++;
            }
            if (!(isspace(text[i + j]) || ispunct(text[i + j]) || (text[i + j] == '\n') || (text[i + j] == '\t') || (text[i + j] == '\0'))) {
                count--; //if afterw WORD we have more letters => -1 WORD
            }
        } else if ((isspace(text[i + j]) || ispunct(text[i + j]) || (text[i + j] == '\n') || (text[i + j] == '\t')) && text[i + 1 + j] == word[j]) {
            while (text[i + (1 + j)] == word[j] && j != (sizeOfword - 1)) {
                j++;
                index++;
            }
            if (!(index % (sizeOfword - 1))) {
                count++;
            }
            if (!(isspace(text[i + (1 + j)]) || ispunct(text[i + (1 + j)]) || (text[i + (1 + j)] == '\n') || (text[i + (1 + j)] == '\t') || (text[i + (1 + j)] == '\0'))) {
                count--;
            }
        }
    }
    if(count < 0) count = 0;
    return count;
}

double arithmeticMean(int *array, int sizeOfArray){
    double mean = 0;
    for(int i = 0; i < sizeOfArray; i++){
        mean+=array[i];
    }
    return (mean/sizeOfArray);
}

int checkWord(const char *word){
    int index = 0;
    while(word[index]) index++;
    return (index + 1);
}
