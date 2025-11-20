#include <stdio.h>

int main(){
    int c;
    int last_space = 0;

    while((c = getchar()) != EOF){
        if (c == ' '){
            if(last_space == 0)putchar(c);
            last_space = 1;
        }
        else{
            last_space = 0;
            putchar(c);
        }
    }

    return 0;
}
