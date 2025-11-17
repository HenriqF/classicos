#include <stdio.h>
#include <stdlib.h>

int readline(char** line, size_t* size){
    *size = 0;
    char* resultado = malloc(1);
    if (!resultado) return -1;

    char c;
    while((c = getchar()) != '\n'){
        char* temp = realloc(resultado, ((*size)+2));
        if (!temp){
            free(resultado);
            return -1;
        } 
        resultado = temp;

        resultado[*size]=c;
        (*size)++;
    }
    resultado[*size]='\0';

    *line = resultado;
    return 0;
}

int main(){
    char* line;
    size_t size;
    
    readline(&line, &size);
    printf("%zu, %s", size, line);
    readline(&line, &size);
    printf("%zu, %s", size, line);

    return 0;
}