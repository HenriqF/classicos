#include <stdio.h>
#include <stdlib.h>

void listArr(int* arr, int size){
    printf("[");
    for(int i = 0; i<size-1; i++){
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[size-1]);
    printf("]");
}

void arraySum(int** arr, int* size){
    *arr = realloc(*arr, (*size+1)*sizeof(int));
    int s = 0;
    for(int i = 0; i<*size;i++){
        s += (*arr)[i]; 
    }
    (*arr)[*size] = s;
    *size = ++(*size);
    listArr(*arr, *size);
}



int main(){
    int size = 1;
    int* arr = malloc(size*sizeof(int));
    for(int i = 0; i<size; i++){
        arr[i] = i+1;
    }

    for (int i = 0; i< 20; i++){
        arraySum(&arr, &size);
        printf("\n");
    }
    

    
    return 0;
}