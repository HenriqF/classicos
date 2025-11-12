#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int max(int a, int b){
    return (a>b)? a : b;
}
int min(int a, int b){
    return (a<b)? a : b;
}

int main(){
    char* password = NULL;
    size_t t = 0;
    size_t size = getline(&password, &t, stdin);

    if (size == -1){
        printf("deu merda");
        return 1;
    }
    if (size > 0){
        if (password[size-1] == '\n'){
            password[size-1] = '\0';
        }
    }

    double total_score = 100;


    //tamanho
    double mult_size = 1;
    if (size <= 8)mult_size = 0.3;
    else if (size > 8 && size <= 12) mult_size = 0.6;
    

    //variedade

    int maiuscula = 0;
    int minuscula = 0;
    int numero = 0;
    int especial = 0;

    for(int i = 0; password[i]!='\0';i++){
        char c = (char)password[i];
        if(isupper(c)) maiuscula += 1;
        else if(islower(c)) minuscula += 1;
        else if(isdigit(c)) numero += 1;
        else especial += 1;
    }
    
    //numeros
    double diff = max(max(maiuscula, minuscula), max(numero,especial)) - min(min(maiuscula,minuscula), min(numero,especial));
    diff = 1.0 - ((double)diff / (size * 2.0));
    if (diff<0) diff = 0;

    double mult_variety = 1*diff;


    free(password);
    printf("escore total: %.1lf%% forte", total_score*mult_size*mult_variety);
    return 0;
}