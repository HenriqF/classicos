#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

//deve contar:
//  caracteres, digitos, pontuacao.
//  palavras, numeros.
//intervalos:
//  letras: Maiusculas | 65 -> 90    Minusculas | 97 -> 122   Espaços | 32
//  numeros: Digitos   | 48 -> 57
//  pontuacao: Simples | 33 -> 47 (fodase o resto)
// tinha um .h pra isso...

int main(){
    setlocale(LC_CTYPE, "");
    char* content;
    size_t size;
    FILE* file = fopen("read.txt", "rb");
    if (file == NULL){
        printf("Deu merda");
        return 1;
    }
    else{
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);

        content = malloc(size+1);
        if (content){
            size = fread(content, 1, size, file);
            content[size] = '\0';
        }
        fclose(file);
    }
    content[size] = '\0';

                                    // 0   1   2   3   4   5   6
    int stats[7] = {0,0,0,0,0,0,0}; // car dig pon esp mis pal num

    int currentP = 0, currentN = 0;
    for (int i =0; i< size; i++){
        int c = (unsigned char)content[i];
        if (isalpha(c)){
            stats[0]++;
            currentP = 1;
            continue;
        }
        if (currentP == 1) stats[5]++, currentP = 0;
        if (isdigit(c)){
            stats[1]++;
            currentN = 1;
            continue;
        }
        if (currentN == 1) stats[6]++, currentN = 0;

        if (ispunct(c)){
            stats[2]++;
        }
        else if (isspace(c)){
            stats[3]++;
        }
        else{
            stats[4]++;
        }  
    }
    if (currentP == 1) stats[5]++, currentP = 0;
    if (currentN == 1) stats[6]++, currentN = 0;

    free(content);

    FILE* file2 = fopen("stats.txt", "w");
    if (file2 == NULL){
        printf("Deu merda (parte 2)");
        return 1;
    }
    char buffer[2048];
    snprintf(buffer, sizeof(buffer),
         "Estatisticas:\n"
         "  caracteres: %d\n"
         "  digitos: %d\n"
         "  pontuação: %d\n"
         "  espaços: %d\n"
         "  miscelaneos: %d\n\n"
         "  palavras: %d\n"
         "  numeros: %d\n"
         , stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6]);
    fprintf(file2,"%s", buffer);
    fclose(file2);

    printf("Analise em stats.txt.");
    return 0;
}