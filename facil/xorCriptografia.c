#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char* codificar(const char* mensagem, const char* chave){
    int mensagemLen = strlen(mensagem);
    int chaveLen = strlen(chave);

    char* resultado = malloc(mensagemLen+1);
    if (!resultado){printf("deu merda"); return NULL;} 

    for (int i = 0; i < mensagemLen; i++){
        resultado[i] = mensagem[i]^chave[i%chaveLen];
    }

    resultado[mensagemLen] = '\0';
    return resultado;
}

int main(){
    char* mensagem = NULL;
    size_t mensagemBuf = 0;
    char* chave = NULL;
    size_t chaveBuf = 0;

    printf("Mensagem: \n");
    getline(&mensagem, &mensagemBuf, stdin);
    printf("Chave: \n");
    getline(&chave, &chaveBuf, stdin);

    mensagem[strcspn(mensagem, "\n")] = '\0';
    chave[strcspn(chave, "\n")] = '\0';

    char* resultado = NULL;
    resultado = codificar(mensagem, chave);
    printf("Resultado: << %s >>\n\nCopiar para a clipboard? Y/N\n", resultado);

    char resposta = 'N';
    scanf(" %c", &resposta);

    if (resposta == 'Y'){
        size_t reslen = strlen(resultado)+1;    
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, reslen);
        memcpy(GlobalLock(hMem), resultado, reslen);

        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }

    free(mensagem);
    free(chave);
    return 0;
}