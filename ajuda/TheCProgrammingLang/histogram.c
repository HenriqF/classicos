//até entao, nada de alocacao dinamica, portanto, tem que definir quantas letras a palavra pode ter
#include <stdio.h>
#include <stdbool.h>

#define MAXLENGTH 46 //The longest English word is pneumonoultramicroscopicsilicovolcanoconiosis (45 letters)


int max(int a,int b){
    return (a>b) ? a : b;
}

int main(){
    int count[MAXLENGTH];
    for (int i = 0; i <= MAXLENGTH; i++){
        count[i] = 0;
    }

    int c;
    int current_length = 0;
    int max_freq = 0;
    while((c = getchar()) != EOF){
        if ((c == ' ' || c == '\n' || c == '\t') || (c >= '0' && c <= '9')){
            if(current_length < MAXLENGTH && current_length != 0){
                count[current_length]++;
                max_freq = max(max_freq, count[current_length]);
            }
            current_length = 0;
        }
        else{
            current_length++;
        }
    }
    count[current_length]++;
    if(current_length != 0) max_freq = max(max_freq, count[current_length]);
    
    
    int lower_limit = 1;
    int higher_limit = MAXLENGTH;

    while(count[lower_limit] == 0) lower_limit++;
        
    while(count[higher_limit-1] == 0) higher_limit--;

    for (int i = max_freq; i > 0 ; i--){
        for(int j = lower_limit; j <higher_limit; j++){
            if(count[j] >= i){
                printf("  #");
            }
            else{
                printf("   ");
            }
            
        }
        printf("\n");
    }

    printf("\n");
    for(int j = lower_limit; j <higher_limit; j++){
        printf("%3d", j);
    }
}