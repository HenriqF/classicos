#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NORMAL "\x1B[0m"
#define VERM  "\x1B[31m"
#define AMRL "\x1B[33m"
#define VERD  "\x1B[32m"

// nao funciona bem ,compara os textos de forma ingenua e serve so pra falar que foi feito

char* contentA;
char** linhasA;
int qtdLinhasA;
size_t sizeA;

char* contentB;
char** linhasB;
int qtdLinhasB;
size_t sizeB;

void getFileContents(){
    FILE* filea = fopen("a.txt", "rb");
    FILE* fileb = fopen("b.txt", "rb");
    if (filea == NULL || fileb == NULL){
        printf("Deu merda");
        if (filea) fclose(filea);
        if (fileb) fclose(fileb);
        return;
    }
    else{
        fseek(filea, 0, SEEK_END);
        fseek(fileb, 0, SEEK_END);
        sizeA = ftell(filea);
        sizeB = ftell(fileb);
        rewind(filea);
        rewind(fileb);

        contentA = malloc(sizeA+1);
        contentB = malloc(sizeB+1);

        if (!contentA || !contentB){
            printf("deu merda"); 
            free(contentA);
            free(contentB);
            fclose(filea);
            fclose(fileb);
            return;
        }

        sizeA = fread(contentA, 1, sizeA, filea);
        contentA[sizeA] = '\0';
        sizeB = fread(contentB, 1, sizeB, fileb);
        contentB[sizeB] = '\0';

        fclose(filea);
        fclose(fileb);
    }
}

char** getLines(char* content, int size, int* lineCount){
    int lines = 0;
    for (int i = 0; i < size; i++){
        if (content[i] == '\n') lines++;
    }
    if (size > 0 && content[size-1] != '\n') lines++;
    *lineCount = lines;

    char** linhas = malloc(lines*sizeof(char*));
    if (!linhas){
        printf("deu merda");
        return NULL;
    }

    int lineCounter=0;
    int startIndex = 0;
    for(int i = 0; i <= size; i++){
        if (i == size || content[i] == '\n'){
            int length;
            if(content[i-1] == '\r') length = i-1 - startIndex;
            else length = i - startIndex;

            char* currentLine = malloc(length+1);
            if (!currentLine){
                printf("deu merda");
                return linhas;
            }
            memcpy(currentLine, &content[startIndex], length);
            currentLine[length] = '\0';
            
            linhas[lineCounter++] = currentLine;
            startIndex = i + 1;
        }
    }
    return linhas;
}

void getDiff(){
    linhasA = getLines(contentA, sizeA, &qtdLinhasA);
    linhasB = getLines(contentB, sizeB, &qtdLinhasB);
    
    int menorLinhaQtd = 0;


    menorLinhaQtd = (qtdLinhasA < qtdLinhasB) ? qtdLinhasA : qtdLinhasB;

    for(int i = 0; i < menorLinhaQtd; i++){
        if(strcmp(linhasA[i], linhasB[i]) == 0){
            printf("%d ~ %s\n", i+1, linhasA[i]);
        }
        else{
            printf("%s%d !%s %s %s->%s ", AMRL,i+1,NORMAL,linhasA[i],AMRL,NORMAL);
            printf("%s\n", linhasB[i]);
        }
    }
    if (qtdLinhasA > qtdLinhasB){
        for(int i = qtdLinhasB; i < qtdLinhasA; i++){
            printf("%s%d -%s %s\n", VERM,i+1,NORMAL, linhasA[i]);
        }
    }
    else{
        for(int i = qtdLinhasA; i < qtdLinhasB; i++){
            printf("%s%d +%s %s\n", VERD,i+1,NORMAL, linhasB[i]);
        }
    }

    return;
}

int main(){
    getFileContents();
    getDiff();
    return 0;
}