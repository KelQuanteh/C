#include <stdio.h>

int main(){
    int a, b, soma;
    float media; 

    a= 6;
    b= 12;

    soma= a + b;
    media= soma/2.0;

    printf("a soma de %d e %d eh %d \n", a, b, soma);
    printf("a media de %d e %d eh %f \n", a, b, media);

    return 0;
}