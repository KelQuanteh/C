#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define ATTACK_REPORT_FILE "R_ATAQUES.txt"
#define ENTITY_REPORT_FILE "R_ENTIDADES.txt"
#define SIZE_REPORT_FILE "R_TAMANHO.txt"
#define FIREWALL_CONFIG_FILE "BLACKLIST.bl"

#include "log.h"


void valida_arff(FILE *arff, atributo *atributos, int quantidade) {
  // Receba um arquivo ARFF com um ponteiro de leitura antes de "@data"; passe por todas as linhas de dados e valide cada elemento em cada coluna
  char line[2048];
  int lineNumber = 0;
  int attributeCount = 0;

  while (fgets(line, sizeof(line), arff)) {
    lineNumber++;

    // Verifique se a linha começa com '@' (se é um atributo ou não)
    if (line[0] == '@') {
      attributeCount++;
    } else {
      // senão
      char *token;
      char *saveptr;
      int attributeIndex = 0;

      token = strtok_r(line, ",", &saveptr);
      while (token != NULL && attributeIndex < quantidade) {
        if (strcmp(atributos[attributeIndex].tipo, "categorical") == 0) {
          // Validar valor do atributo categórico
          if (strchr(token, '{') == NULL || strchr(token, '}') == NULL) {
            fprintf(stderr, "Erro: valor de atributo categórico inválido na linha %d\n", lineNumber);
          }
        } else {
          // Validar outros tipos de atributos
          if (strcmp(atributos[attributeIndex].tipo, "numeric") == 0) {
            // Validar valor do atributo numérico
            float value;
            if (sscanf(token, "%f", &value) != 1) {
              fprintf(stderr, "Erro: valor de atributo numérico inválido na linha %d\n", lineNumber);
            }
          } else if (strcmp(atributos[attributeIndex].tipo, "string") == 0) {
            // Validar valor do atributo string
            if (strlen(token) == 0) {
              fprintf(stderr, "Erro: valor de atributo string inválido na linha %d\n", lineNumber);
            }
          }
        }

        attributeIndex++;
        token = strtok_r(NULL, ",", &saveptr);
      }

      // Verifique se o número de atributos na linha de dados corresponde à contagem esperada
      if (attributeIndex != quantidade) {
        fprintf(stderr, "Erro: Número incorreto de atributos na linha %d\n", lineNumber);
      }
    }
  }

  // Verifique se o número de atributos declarados corresponde à contagem esperada
  if (attributeCount != quantidade) {
    fprintf(stderr, "Erro: Número incorreto de atributos declarados\n");
  }
}


// Função para verificar se um endereço IP é benigno
bool isBenign(const char *value) {
    //Endereços IP no intervalo 192.168.0.0 - 192.168.255.255 como benignos.
    if (strncmp(value, "192.168.", 8) == 0) {
        return true;
    }
    return false;
}


// Função para verificar se um endereço IP é potencialmente malicioso
bool isPotentialMalicious(const char *value) {
    // IP addresses starting with "10." as potentially malicious.
    if (strncmp(value, "10.", 3) == 0) {
        return true;
    }
    return false;
}


//Função para verificar se um endereço IP é malicioso
bool isMalicious(const char *value) {
    if (strncmp(value, "192.168.1.", 10) == 0) {
        return true;
    }
    return false;
}


//Função para gerar relatórios de ataque
void generate_attack_reports(atributo *atributos, int quantidade, FILE* file) {
  FILE *reportFile = fopen(ATTACK_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Error creating %s\n", ATTACK_REPORT_FILE);
    exit(5);
  }

  //PKT_CLASS é o atributo que representa o tipo de ataque
  int i, j;
  char **attackTypes = (char **)malloc(quantidade * sizeof(char *));
  int *attackCounts = (int *)malloc(quantidade * sizeof(int));
  if (!attackTypes || !attackCounts) {
    fprintf(stderr, "Erro de alocação de memória\n");
    exit(6);
  }

  for (i = 0; i < quantidade; i++) {
    attackTypes[i] = strdup(atributos[i].rotulo);
    attackCounts[i] = 0;
  }

  char line[2048];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != '@') { // linhas de 'data' não comecam com '@'
      char *token = strtok(line, ",");
      if (token) {
        for (j = 0; j < quantidade; j++) {
          if (strcmp(token, attackTypes[j]) == 0) {
            // o PKT_CLASS é o atributo que representa o tipo de ataque
            if (strcmp(atributos[j].rotulo, "PKT_CLASS") == 0) {
              char *value = strtok(NULL, ",");
              if (value && strcmp(value, "Normal") != 0) {
                attackCounts[j]++;
              }
            }
          }
        }
      }
    }
  }

  // Grava os relatórios de ataque em R_ATAQUES.txt
  for (i = 0; i < quantidade; i++) {
    if (attackCounts[i] > 0) {
      fprintf(reportFile, "%s;%d\n", attackTypes[i], attackCounts[i]);
    }
    free(attackTypes[i]);
  }

  fclose(reportFile);
  free(attackTypes);
  free(attackCounts);
}


//Função para gerar relatórios de entidade
void generate_entity_reports(atributo *atributos, int quantidade, FILE* file) {
  FILE *reportFile = fopen(ENTITY_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Erro ao criar %s\n", ENTITY_REPORT_FILE);
    exit(8);
  }

  // Inicialize contadores para entidades benignas, potencialmente maliciosas e maliciosas
  int benignCount = 0;
  int potentialMaliciousCount = 0;
  int maliciousCount = 0;

  char line[2048];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != '@') { // desde que linhas de dados não comecem com '@'
      char *token = strtok(line, ",");
      if (token) {
        // Como o SRC_ADD é o atributo que representa os endereços IP de origem
        if (strcmp(atributos[0].rotulo, "SRC_ADD") == 0) {
          char *value = strtok(NULL, ",");
          if (value) {
            // use uma estrutura de dados para acompanhar as classificações de IP e atualizar os contadores de acordo.
            if (isBenign(value)) {
              benignCount++;
            } else if (isPotentialMalicious(value)) {
              potentialMaliciousCount++;
            } else {
              maliciousCount++;
            }
          }
        }
      }
    }
  }

  // Grava os relatórios da entidade em R_ENTIDADES.txt
  fprintf(reportFile, "Benigno;%d\n", benignCount);
  fprintf(reportFile, "Potencialmente Malicioso;%d\n", potentialMaliciousCount);
  fprintf(reportFile, "Malicioso;%d\n", maliciousCount);

  fclose(reportFile);
}


//Função para gerar relatórios de tamanho
void generate_size_reports(atributo *atributos, int quantidade, FILE* file) {
  FILE *reportFile = fopen(SIZE_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Erro ao criar %s\n", SIZE_REPORT_FILE);
    exit(10);
  }

  // desde que PKT_CLASS é o atributo que representa o tipo de ataque
   // como PKT_AVG_SIZE é o atributo que representa o tamanho médio do pacote
  int i, j;
  char **attackTypes = (char **)malloc(quantidade * sizeof(char *));
  double *avgSizes = (double *)malloc(quantidade * sizeof(double));
  int *counters = (int *)malloc(quantidade * sizeof(int));
  if (!attackTypes || !avgSizes || !counters) {
    fprintf(stderr, "Erro de alocação de memória\n");
    exit(11);
  }

  for (i = 0; i < quantidade; i++) {
    attackTypes[i] = strdup(atributos[i].rotulo);
    avgSizes[i] = 0.0;
    counters[i] = 0;
  }

  char line[2048];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != '@') { // desde que linhas de dados não comecem com '@'
      char *token = strtok(line, ",");
      if (token) {
        // Como PKT_CLASS é o atributo que representa o tipo de ataque
        // Assumindo que PKT_AVG_SIZE é o atributo que representa o tamanho médio do pacote
        for (j = 0; j < quantidade; j++) {
          if (strcmp(token, attackTypes[j]) == 0) {
            char *value = strtok(NULL, ",");
            if (value) {
              // Como PKT_CLASS é o atributo que representa o tipo de ataque
              if (strcmp(atributos[j].rotulo, "PKT_CLASS") == 0) {
                double avgSize = atof(strtok(NULL, ","));
                avgSizes[j] += avgSize;
                counters[j]++;
              }
            }
          }
        }
      }
    }
  }


  // Grava os relatórios de tamanho em R_TAMANHO.txt
  for (i = 0; i < quantidade; i++) {
    if (counters[i] > 0) {
      double avgSize = avgSizes[i] / counters[i];
      fprintf(reportFile, "%s;%.2lf\n", attackTypes[i], avgSize);
    }
    free(attackTypes[i]);
  }

  fclose(reportFile);
  free(attackTypes);
  free(avgSizes);
  free(counters);
}


//Função para gerar um arquivo de configuração do firewall
void generate_firewall_config(atributo *atributos, int quantidade, FILE* file) {
  FILE *configFile = fopen(FIREWALL_CONFIG_FILE, "w");
  if (!configFile) {
    fprintf(stderr, "Error creating %s\n", FIREWALL_CONFIG_FILE);
    exit(13);
  }

  char **maliciousIPs = (char **)malloc(quantidade * sizeof(char *));
  int maliciousCount = 0;

  char line[2048];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] != '@') { // como as linhas de dados começam com não-@
      char *token = strtok(line, ",");
      if (token) {
        if (strcmp(atributos[0].rotulo, "PKT_CLASS") == 0) {
          char *value = strtok(NULL, ",");
          if (value && strcmp(value, "Normal") != 0) {
            char *ipAddress = strtok(NULL, ",");
            if (ipAddress) {
              // adicione o endereço IP à matriz maliciosoIPs se for considerado malicioso
              
              if (isMalicious(value)) {
                maliciousIPs[maliciousCount++] = strdup(ipAddress);
              }
            }
          }
        }
      }
    }
  }


  // Escreva os endereços IP maliciosos em BLACKLIST.bl
  for (int i = 0; i < maliciousCount; i++) {
    fprintf(configFile, "%s\n", maliciousIPs[i]);
    free(maliciousIPs[i]);
  }

  fclose(configFile);
  free(maliciousIPs);
}
