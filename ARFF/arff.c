#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#include "arff.h"

// Função para exibir informações sobre os atributos
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
        if (infos[i].categorias) {
            printf("Categorias: ");
            for (int j = 0; infos[i].categorias[j] != NULL; j++) {
                printf("%s ", infos[i].categorias[j]);
            }
            printf("\n");
        }
        if (i < tamanho - 1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

// Função para contar o número de atributos em um arquivo ARFF
int conta_atributos(FILE *arff) {
    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), arff) != NULL) {
        if (strstr(line, "@attribute") == line) {
            count++;
        } else if (strstr(line, "@data") == line) {
            break; 
        }
    }

    rewind(arff); // Redefinir o ponteiro do arquivo para o início
    return count;
}

// Função para processar as categorias de um atributo nominal
void processa_categorias(atributo *elemento, char *categorias) {
  char *token;
  char *saveptr;
  int i = 0;

  token = strtok_r(categorias, ",", &saveptr);

  while (token != NULL) {
    
    elemento->categorias[i] = strdup(token);
    token = strtok_r(NULL, ",", &saveptr);
    i++;
  }
}

// Função para processar todos os atributos de um arquivo ARFF
atributo* processa_atributos(FILE *arff, int quantidade) {
  
  int i;
  char line[1024];
  atributo *atributos = (atributo *)malloc(quantidade * sizeof(atributo));

  for (i = 0; i < quantidade; i++) {
    atributos[i].categorias = NULL; 

    fgets(line, sizeof(line), arff);

    // Extrai rótulo, tipo e categorias (se houver)
    char *token;
    char *saveptr;
    int part = 0;

    token = strtok_r(line, " \t\n", &saveptr);

    while (token != NULL) {
      if (part == 1) {
        atributos[i].rotulo = strdup(token);
      } else if (part == 2) {
        atributos[i].tipo = strdup(token);
        if (strcmp(atributos[i].tipo, "categorical") == 0) {
          // Lida com atributos categóricos, extrai categorias
          token = strtok_r(NULL, "{", &saveptr);
          if (token != NULL) {
            processa_categorias(&atributos[i], token);
          }
        }
      }
      part++;
      token = strtok_r(NULL, " \t\n", &saveptr);
    }
  }

  return atributos;
}
