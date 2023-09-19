#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float squrt(float x) {
    float s = sqrt(x);
    return s;
}

float cubrt(float x) {
    float s = cbrt(x);
    return s;
}

float ceiling(float x) {
    float s = ceil(x);
    return s;
}

float floore(float x) {
    float s = floor(x);
    return s;
}

void leVetor(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%f", &arr[i]);
    }
}

void imprimeVetor(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main() {
    int tam;
    char op[6];

    printf("Entre o tamanho do vetor: \n");
    scanf("%d", &tam);

    float* vet = (float*)malloc(tam * sizeof(float));
    if (vet == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Entre com os números reais:\n");
    leVetor(vet, tam);

    printf("Entre com um operador: sqrt, cbrt, ceil, floor\n");
    scanf(" %c", op);

    float (*sq)(float);
    sq = squrt;

    float (*cb)(float);
    cb = cubrt;

    float (*ce)(float);
    ce = ceiling;

    float (*fl)(float);
    fl = floore;

    if (strcmp(op, "sqrt") == 0) {
        for (int i = 0; i < tam; i++) {
            vet[i] = sq(vet[i]);
        }
    } else if (strcmp(op, "cbrt") == 0) {
        for (int i = 0; i < tam; i++) {
            vet[i] = cb(vet[i]);
        }
    } else if (strcmp(op, "ceil") == 0) {
        for (int i = 0; i < tam; i++) {
            vet[i] = ce(vet[i]);
        }
    } else if (strcmp(op, "floor") == 0) {
        for (int i = 0; i < tam; i++) {
            vet[i] = fl(vet[i]);
        }
    } else {
        printf("Operador inválido.\n");
    }

    imprimeVetor(vet, tam);

    free(vet);

    return 0;
}