#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//O código inclui os cabeçalhos necessários e define uma mensagem de ajuda para exibir quando o programa é executado com argumentos inválidos.

#include "arff.h"
#include "log.h"

#define HELP "Forma de uso: ./arff -i <arq_in> [-p -v -a -b -c -d]\n"

//A função main é a função principal do programa. Ela declara variáveis para armazenar as opções de linha de comando e o nome do arquivo de entrada.
int main(int argc, char **argv) {
  int opt;
  char exibicao = 0;
  char validacao = 0;
  char ataques = 0;
  char entidades = 0;
  char tamanho = 0;
  char firewall = 0;
  char *entrada = 0;

  //Este trecho de código usa a função getopt para analisar as opções de linha de comando. Cada opção é especificada por uma letra após o caractere -. 
  //-i indica o nome do arquivo de entrada. As variáveis de controle são definidas de acordo com as opções fornecidas.
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

//Verifica se o nome do arquivo de entrada foi fornecido. Se não foi, exibe a mensagem de ajuda e sai do programa.
  if (!entrada) {
    fprintf(stderr, HELP);
    exit(2);
  }

//Abre o arquivo de entrada especificado para leitura. Se o arquivo não puder ser aberto, exibe uma mensagem de erro e sai do programa.
  FILE *arquivo = fopen(entrada, "r");
  if (!arquivo) {
    fprintf(stderr, "Não foi possível abrir o arquivo informado!\n");
    exit(3);
  }

//Chama a função conta_atributos para contar o número de atributos no arquivo ARFF. Se houver um erro (-1), exibe uma mensagem de erro e sai do programa. 
//Se não houver atributos (0), também exibe uma mensagem de erro e sai.
  int qntd_atributos = conta_atributos(arquivo);
  if (qntd_atributos < 0) {
    fprintf(stderr, "Erro ao contar os atributos no arquivo fornecido!\n");
    exit(4);
  } else if (qntd_atributos == 0) {
    fprintf(stderr, "O arquivo não possui atributos!\n");
    exit(5);
  }

//Chama a função processa_atributos para ler e processar os atributos do arquivo ARFF. Os atributos são armazenados em uma estrutura de dados chamada atributo.
  atributo *dados_atributos = processa_atributos(arquivo, qntd_atributos);

//Com base nas opções de linha de comando, o programa chama várias funções para gerar relatórios e executar outras operações relacionadas à análise do arquivo ARFF.
  if (exibicao) {
    exibe_atributos(dados_atributos, qntd_atributos);
  }
  if (validacao) {
    rewind(arquivo);
    valida_arff(arquivo, dados_atributos, qntd_atributos);
  }
  if (ataques) {
    generate_attack_reports(dados_atributos, qntd_atributos, arquivo);
  }
  if (entidades) {
    generate_entity_reports(dados_atributos, qntd_atributos, arquivo);
  }
  if (tamanho) {
    generate_size_reports(dados_atributos, qntd_atributos, arquivo);
  }
  if (firewall) {
    generate_firewall_config(dados_atributos, qntd_atributos, arquivo);
  }

  // liberar a memória alocada dinamicamente e fechar o arquivo de entrada antes de encerrar o programa.

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
