#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char *rotulo;
    char *tipo;
    char *categorias;
} atributo;

void exibe_atributos(atributo *infos, int tamanho) {
    if (infos == NULL) {
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(1);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("-> Atributo #%d\n", i + 1);
        printf("Rótulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
        if (i < tamanho - 1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff) {
    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), arff) != NULL) {
        if (strstr(line, "@attribute") == line) {
            count++;
        } else if (strstr(line, "@data") == line) {
            break; // Attribute section ends
        }
    }

    rewind(arff); // Reset file pointer to the beginning
    return count;
}

atributo *processa_atributos(FILE *arff, int numAtributos) {
    atributo *infos = (atributo *)malloc(numAtributos * sizeof(atributo));
    char line[1024];
    int currentAttribute = 0;

    while (fgets(line, sizeof(line), arff) != NULL) {
        if (strstr(line, "@attribute") == line) {
            char *label = strtok(line, " ");
            char *tipo = strtok(NULL, " ");
            char *categorias = NULL;

            // Check if it's a categorical attribute
            if (strstr(tipo, "{") != NULL) {
                tipo = "categoric";
                strtok(tipo, "{"); // Remove '{' from tipo
                categorias = strtok(NULL, "}");
            }

            infos[currentAttribute].rotulo = strdup(label);
            infos[currentAttribute].tipo = strdup(tipo);
            if (categorias) infos[currentAttribute].categorias = strdup(categorias);
            else infos[currentAttribute].categorias = NULL;

            currentAttribute++;
        } else if (strstr(line, "@data") == line) {
            break; // Attribute section ends
        }
    }

    rewind(arff); // Reset file pointer to the beginning
    return infos;
}

int main(int argc, char **argv) {
    int opt;
    char exibicao = 0;
    char *entrada = NULL;
    FILE *arff = NULL;

    while ((opt = getopt(argc, argv, "pi:")) != -1) {
        switch (opt) {
        case 'i':
            entrada = strdup(optarg);
            break;
        case 'p':
            exibicao = 1;
            break;
        default:
            fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
            exit(1);
        }
    }

    if (entrada == NULL) {
        fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
        exit(2);
    }

    arff = fopen(entrada, "r");
    if (arff == NULL) {
        perror("Erro ao abrir o arquivo");
        free(entrada);
        exit(3);
    }

    int numAtributos = conta_atributos(arff);
    if (numAtributos <= 0) {
        printf("Arquivo ARFF inválido ou não possui atributos.\n");
        fclose(arff);
        free(entrada);
        exit(4);
    }

    atributo *atributos = processa_atributos(arff, numAtributos);

    fclose(arff);
    free(entrada);

    if (exibicao) {
        exibe_atributos(atributos, numAtributos);
    }

    // Clean up memory
    for (int i = 0; i < numAtributos; i++) {
        free(atributos[i].rotulo);
        free(atributos[i].tipo);
        free(atributos[i].categorias);
    }
    free(atributos);

    return 0;
}
