#include <stdio.h>

#define MAXLEN 1000

int getLine(char string[], int length); //ignora \n do fim.
void reverseLine(char line[], int length); 
int main(){
    char linha[MAXLEN];
    int len = 0;

    while ((len = getLine(linha, MAXLEN)) != 0){
        reverseLine(linha, len);
        printf("%s\n", linha);
    }
}

int getLine(char string[], int length){
    int c, i;
    for(i = 0; i < length-1 && (c = getchar()) != EOF && c!='\n'; i++){
        string[i] = c;
    }
    string[i] == '\0';
    return i;
}

void reverseLine(char line[], int length){
    int steps = length/2;
    int end = length-1;
    for(int start = 0; start<steps; start++, end--){
        if(line[start] != line[end]){
            line[start] ^= line[end];
            line[end] ^= line[start];
            line[start] ^= line[end];
        }
    }
    line[length] = '\0';
}