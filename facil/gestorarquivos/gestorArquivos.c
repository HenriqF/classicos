#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void logUpdate(const char* mensagem){
    FILE *file = fopen("changelog.txt", "a");
    fprintf(file, "%s\n", mensagem);
    fclose(file);
}

void copy(const char* fonte, const char* dest){
    WIN32_FIND_DATA fd;
    char fontePath[MAX_PATH];
    char destPath[MAX_PATH];
    CreateDirectory(dest, NULL);

    sprintf(fontePath, "%s\\*", fonte);
    HANDLE hFind = FindFirstFile(fontePath, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        if (strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..")){
            sprintf(fontePath, "%s\\%s", fonte, fd.cFileName);
            sprintf(destPath, "%s\\%s", dest, fd.cFileName);

            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                copy(fontePath, destPath);
            } 
            else{
                char buffer[1024];
                if (GetFileAttributes(destPath) != INVALID_FILE_ATTRIBUTES){
                    sprintf(buffer, "Foi atualizado: %s", destPath);
                }
                else{
                    sprintf(buffer, "Novo arquivo: %s", destPath);
                }
                logUpdate(buffer);

                CopyFile(fontePath, destPath, FALSE);
            }
        }
    } while (FindNextFile(hFind, &fd));

    FindClose(hFind);
}

int main(){
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeBuffer[64];
    strftime(timeBuffer, sizeof(timeBuffer),"%Y-%m-%d %H:%M:%S", t);
    
    char buffer[1024];
    sprintf(buffer, "\nNovo manuseio: %s", timeBuffer);
    logUpdate(buffer);
    logUpdate("==== Pegar arquivos ====");

    const char* fonte = "";
    const char* destino = "";

    copy(fonte, destino);

    char resposta = 'N';
    while (resposta != 'Y'){
        printf("Alteracoes completas? Y/N\n");
        scanf(" %c", &resposta);

    }
    logUpdate("==== Guardar arquivos ====");
    copy(destino, fonte);

    return 0;
}