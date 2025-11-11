#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define NORMAL "\x1B[0m"
#define VERM  "\x1B[31m"
#define AMRL "\x1B[33m"
#define VERD  "\x1B[32m"

char* content;
size_t size;

int readListLine(int index){
    //le a linha da lista, ( que inicia em index) 
    int prioridade = 0;
    if (content[index+2] == '-'){
        switch (content[index]){
            case 'O':
                prioridade=3;
                break;
            case 'o':
                prioridade=2;
                break;
            case '.':
                prioridade=1;
                break;
            default:
                break;
        }
    }

    for (int i = index; i < size; i++){
        char c = content[i];
        if (c == '\n') return i+1;
        if (prioridade == 3) printf("%s%c%s", VERM, c, NORMAL);
        if (prioridade == 2) printf("%s%c%s", AMRL, c, NORMAL);
        if (prioridade == 1) printf("%s%c%s", VERD, c, NORMAL);
        if (prioridade == 0) printf("%c", c);
    }
}

void showList(){
    int i = 0;
    do{
        i = readListLine(i);
        printf("\n");
    }while (i<size);
}

void newTask(){
    char* linha = NULL;
    char respostaPri;
    size_t size = 0;
    int ch;

    printf("Escreva tarefa:\n");
    while((ch = fgetc(stdin)) != EOF && ch != '\n'){
        linha = realloc(linha, size+2);
        if (!linha) return;
        linha[size++] = (char)ch;
        linha[size] = '\0';
    }
    printf("Defina prioridade (O, o, .):\n");
    scanf(" %c", &respostaPri);
    if (respostaPri != 'O' && respostaPri != 'o' && respostaPri != '.') respostaPri = '.';

    char* tarefa = malloc(size+5);
    sprintf(tarefa, "%c - %s", respostaPri, linha);
    
    FILE* f = fopen("todo.txt", "a");
    if (f == NULL){
        printf("Deu merda");
    }
    else{
        fprintf(f, "\n%s", tarefa);
        fclose(f);
    }
    
    free(linha);
}

void markTask(){
    int i = 0;
    int l = 1;
    do{
        printf("Tarefa %d : ", l);
        i = readListLine(i);
        l++;
        printf("\n");
    }while (i<size);

    int tarefa;
    printf("Qual tarefa marcar? \n");
    scanf("%d", &tarefa);

    if (tarefa<1 || tarefa > l){
        return;
    }
    else{
        if (tarefa == 1){
            content[2] = '!';
            i = 2;
        } 
        else{
            int c = 0;
            int i = 0;
            while(i++ < size){
                if (content[i] == '\n') c++;
                if (c == tarefa-1) break;
            }
            i+=3;
            content[i] = '!';
        }
        FILE* f = fopen("todo.txt", "wb");
        if (!f){
            printf("deu merda");
            return;
        }
        fprintf(f, "%s", content);   
        fclose(f);
    }
}

void updateContentVar(){
    FILE* f = fopen("todo.txt", "rb");
    if (f == NULL){
        printf("Deu merda");
        return;
    }
    else{
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        content = malloc(size+1);
        if (content){
            size = fread(content, 1, size, f);
            content[size] = '\0';
        }
        fclose(f);
    }
    showList();
}

int main(){
    setlocale(LC_CTYPE, "");

    char resposta;
    while (resposta!='s'){
        updateContentVar();
        printf("n -> nova tarefa | m -> marcar tarefa | s -> sair\n");
        scanf(" %c", &resposta);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (resposta == 'n') newTask();
        if (resposta == 'm') markTask();
    }

    return 0;
}