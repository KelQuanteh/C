#include <stdio.h>  // Inclui a biblioteca padrão de entrada e saída, necessária para usar funções de entrada/saída, como printf.
#include <math.h>   // Inclui a biblioteca matemática, que fornece funções matemáticas, como sqrt, pow, etc.
#include "mad.h"     // Inclui um arquivo chamado "mad.h" (presumindo que seja um arquivo de cabeçalho personalizado).

// Definição de funções:

int soma(int a, int b){
    return a + b;  // Retorna a soma dos dois números inteiros a e b.
}

int mult(int a, int b){
    return a * b;  // Retorna o produto dos dois números inteiros a e b.
}

int sub(int a, int b){
    return a - b;  // Retorna a subtração de b de a.
}

int divi(int a, int b){
    return a/b;    // Retorna a divisão inteira de a por b. (Atenção: esta função pode causar erros de divisão por zero se b for zero).
}
