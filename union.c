#include <stdio.h>
#include <stdlib.h>

typedef union uniao_t
{
    char caracteres[21];
    int vet[6];
}uniao;

int main(){
    uniao exemplo;

    exemplo.vet[0] = '2';
    exemplo.vet[1] = '4';
    exemplo.vet[2] = '6';
    exemplo.vet[3] = '8';
    exemplo.vet[4] = '9';
    exemplo.vet[5] = '1';

    exemplo.caracteres[0] = 'T';
    exemplo.caracteres[1] = 'u';
    exemplo.caracteres[2] = 'd';
    exemplo.caracteres[3] = 'o';
    exemplo.caracteres[4] = ' ';
    exemplo.caracteres[5] = 'b';
    exemplo.caracteres[6] = 'e';
    exemplo.caracteres[7] = 'm';
    exemplo.caracteres[8] = '?';


    for (int i = 0; i < sizeof(exemplo.caracteres); i++)
    {
        printf("caracter[%d]: %c \n", i+1, exemplo.caracteres[i]);
    }

    printf("%s \n", exemplo.caracteres);
    

    return 0;
}