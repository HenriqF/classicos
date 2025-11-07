#include <stdio.h>

int fibo(int a, int b){
    printf("%d\n", a+b);
    a+b<1000 ? fibo(b, a+b) : printf("done");
}

int main(){
    fibo(0,1);
    return 0;
}