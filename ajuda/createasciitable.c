#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* file = fopen("tabela.txt", "a");
    for (int i = 0; i < 256; i++){

        char buffer[100];
        sprintf(buffer ,"%d -> %c", i, (char)i);
        fprintf(file, "%s\n", buffer);
    }
    fclose(file);
    printf("%d", (int)' ');

    return 0;
}