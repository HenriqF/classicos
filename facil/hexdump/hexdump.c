#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

char* content;
size_t size;

void readFile(){
    FILE* f = fopen("hex.txt", "rb");
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
}

void hexDump(){
    unsigned int count = 0;

    int i = 0;
    while(i < size){
        
        int j = i;
        printf("%08X ", count);
        while(j < i+16){
            if (j < size) printf("%02X ", content[j]);
            else printf("   ");
            j++;
        }

        int k = i;
        while(k < i+16){
            if (k < size && isprint(content[k])) printf("%c ", content[k]);
            else printf(". ");
            k++;
        }

        if (j < size){
            i = j;
            count += 16;
            printf("\n");
        }
        else{
            return;
        }
    }
}

int main(){
    setlocale(LC_CTYPE, "");
    readFile();
    hexDump();
    return 0;
}