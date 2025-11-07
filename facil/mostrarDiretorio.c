#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

void showDir(const char* dir, int depth){
    WIN32_FIND_DATA fd;
    char dirPath[MAX_PATH];
    HANDLE hFind = FindFirstFile(dir, &fd);

    if (hFind == INVALID_HANDLE_VALUE) return;

    char* espaco = malloc(depth*4+1);
    if (!espaco) exit(1);
    memset(espaco, ' ', depth*4);
    espaco[depth*4] = '\0';

    do{
        if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0){
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                printf("%s Pasta: %s\n", espaco, fd.cFileName);
                

                char basePath[MAX_PATH];
                char newPath[MAX_PATH];
                strcpy(basePath, dir);
                basePath[strlen(basePath)-1] = '\0';
                sprintf(newPath, "%s\\%s\\*", basePath, fd.cFileName);
                showDir(newPath, depth+1);
            } 
            else {
                printf("%s Arquivo: %s\n", espaco, fd.cFileName);
            }
            
        }
    } while(FindNextFile(hFind, &fd));

    free(espaco);
    FindClose(hFind);
}

int main(){
    setlocale(LC_CTYPE, "");

    const char* dir = ""; // Diretorio + estrela : porraloca\\merda\\*"
    showDir(dir, 0);

    return 0;
}