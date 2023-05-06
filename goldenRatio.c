#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n == 0 || n == 1){
        return n;
    }else{
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main(){
    int a;
    scanf("%d", &a);

    int x = fibonacci(a);
    int y = fibonacci(a-1);

    float z = (float)x / (float)y;

    printf("%f\n", z);

    return 0;
}