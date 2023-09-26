#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arff.h"

#define HELP "Forma de uso: ./arff -i <arq_in> [-p -v -a -b -c -d]\n"

int main(int argc, char **argv) {
  int opt;
  char exibicao = 0;
  char validacao = 0;
  char ataques = 0;
  char entidades = 0;
  char tamanho = 0;
  char firewall = 0;
  char *entrada = 0;

  while ((opt = getopt(argc, argv, "pvabcdi:")) != -1) {
    switch (opt) {
      case 'i':
        entrada = strdup(optarg);
        break;
      case 'p':
        exibicao = 1;
        break;
      case 'v':
        validacao = 1;
        break;
      case 'a':
        ataques = 1;
        break;
      case 'b':
        entidades = 1;
        break;
      case 'c':
        tamanho = 1;
        break;
      case 'd':
        firewall = 1;
        break;
      default:
        fprintf(stderr, HELP);
        exit(1);
    }
  }

  if (!entrada) {
    fprintf(stderr, HELP);
    exit(2);
  }

  FILE *arquivo = fopen(entrada, "r");
  if (!arquivo) {
    fprintf(stderr, "Não foi possível abrir o arquivo informado!\n");
    exit(3);
  }

  int qntd_atributos = conta_atributos(arquivo);
  if (qntd_atributos < 0) {
    fprintf(stderr, "Erro ao contar os atributos no arquivo fornecido!\n");
    exit(4);
  } else if (qntd_atributos == 0) {
    fprintf(stderr, "O arquivo não possui atributos!\n");
    exit(5);
  }

  atributo *dados_atributos = processa_atributos(arquivo, qntd_atributos);

  if (exibicao) {
    exibe_atributos(dados_atributos, qntd_atributos);
  }
  if (validacao) {
    rewind(arquivo);
    valida_arff(arquivo, dados_atributos, qntd_atributos);
  }
  if (ataques) {
    generate_attack_reports(dados_atributos, qntd_atributos);
  }
  if (entidades) {
    generate_entity_reports(dados_atributos, qntd_atributos);
  }
  if (tamanho) {
    generate_size_reports(dados_atributos, qntd_atributos);
  }
  if (firewall) {
    generate_firewall_config(dados_atributos, qntd_atributos);
  }

  // Limpe a memória alocada

  for (int i = 0; i < qntd_atributos; i++) {
    free(dados_atributos[i].rotulo);
    free(dados_atributos[i].tipo);
    if (dados_atributos[i].categorias) {
      for (int j = 0; dados_atributos[i].categorias[j] != NULL; j++) {
        free(dados_atributos[i].categorias[j]);
      }
      free(dados_atributos[i].categorias);
    }
  }
  free(dados_atributos);

  free(entrada);
  fclose(arquivo);
  
  return 0;
}
