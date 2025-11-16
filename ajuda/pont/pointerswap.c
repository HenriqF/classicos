#include <stdio.h>
void pointerSwap(int* a, int* b){
    if (a == b){
        return;
    }

    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

int main(){
    int a = 0;
    int b = 20;

    pointerSwap(&b, &b);
    printf("%d %d",a, b);
    return 0;
}