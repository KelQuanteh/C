#include <stdio.h>

typedef struct numComplexo_t {
    int real;
    int imaginary;
} numComplexo_t;

void atribui(numComplexo_t *num) {
    printf("Entre a parte real: ");
    scanf("%d", &num->real);

    printf("Entre a parte imaginaria: ");
    scanf("%d", &num->imaginary);
}

void imprime(numComplexo_t *num) {
    printf("O numero complexo é %d + %di\n", num->real, num->imaginary);
}

void copia(numComplexo_t *x, numComplexo_t *y) {
    y->real = x->real;
    y->imaginary = x->imaginary;
}

void soma(numComplexo_t *x, numComplexo_t *y, numComplexo_t *resultado) {
    resultado->real = x->real + y->real;
    resultado->imaginary = x->imaginary + y->imaginary;
}

int ehReal(numComplexo_t num) {
    return num.imaginary == 0;
}

int main() {
    numComplexo_t complexo1, complexo2, resultado;

    atribui(&complexo1);
    atribui(&complexo2);

    printf("O primeiro numero complexo: ");
    imprime(&complexo1);

    printf("O segundo numero complexo: ");
    imprime(&complexo2);

    copia(&complexo1, &resultado);
    printf("Copia do primeiro numero: ");
    imprime(&resultado);

    soma(&complexo1, &complexo2, &resultado);
    printf("Resultado da soma: ");
    imprime(&resultado);

    if (ehReal(complexo1))
        printf("O primeiro numero é real\n");
    else
        printf("O primeiro numero não é real\n");

    if (ehReal(complexo2))
        printf("O segundo numero é real\n");
    else
        printf("O segundo numero não é real\n");

    return 0;
}
