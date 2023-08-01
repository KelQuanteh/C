#include <stdio.h>

void troca(int* a, int* b){
    int temp= *a; 
    *a= *b; 
    *b= temp; 
}

int main(){
    int a= 5;
    int b= 7; 

    troca(&a, &b);

    printf("a is %d and b is %d", a, b); 

    return 0;
}