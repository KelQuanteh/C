#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "mad.h" // Incluindo um possível arquivo de cabeçalho "mad.h" para funções soma, mult, sub e divi.

int opt; // Declaração de uma variável global para armazenar a opção fornecida via linha de comando.

int main(int argc, char** argv){
    while ((opt = getopt(argc, argv, "a::s::m::d::")) != -1)
    {
        switch (opt)
        {
        case 'a':
            printf("a soma é %d \n", soma(atoi(argv[2]), atoi(argv[3]))); // Calcula a soma de dois números e imprime o resultado.
            break;
        case 'm':
            printf("o produto é %d \n", mult(atoi(argv[2]), atoi(argv[3]))); // Calcula o produto de dois números e imprime o resultado.
            break;
        case 's': 
            printf("o restante é %d \n", sub(atoi(argv[2]), atoi(argv[3]))); // Calcula a subtração de dois números e imprime o resultado.
            break;
        case 'd':
            printf("o quotiente é %d \n", divi(atof(argv[2]), atof(argv[3]))); // Calcula o quociente de dois números e imprime o resultado.
            break;
        default:
            fprintf(stderr, "Usage: %s [-a, -s, -m, -d] num1 num2 \n", argv[0]); // Imprime uma mensagem de uso quando uma opção inválida é fornecida.
            return 1; // Retorna um código de erro.
        }
    }    

    return 0; 
}
