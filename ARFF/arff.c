#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define ATTACK_REPORT_FILE "R_ATAQUES.txt"
#define ENTITY_REPORT_FILE "R_ENTIDADES.txt"
#define SIZE_REPORT_FILE "R_TAMANHO.txt"
#define FIREWALL_CONFIG_FILE "C_IPTABLES.txt"

#include "arff.h"

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

atributo* processa_atributos(FILE *arff, int quantidade) {
  
  int i;
  char line[1024];
  atributo *atributos = (atributo *)malloc(quantidade * sizeof(atributo));

  for (i = 0; i < quantidade; i++) {
    atributos[i].categorias = NULL; 

    fgets(line, sizeof(line), arff);

    // Extraia rótulo, tipo e categorias (se houver)
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
          // Lidar com atributos categóricos, extrair categorias
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

// Function to check if an IP address is malicious
bool isMalicious(const char *value) {
    // Example: Consider IP addresses starting with "192.168.1." as malicious.
    // Replace this with your actual criteria.
    if (strncmp(value, "192.168.1.", 10) == 0) {
        return true;
    }
    return false;
}


// Function to generate attack reports
void generate_attack_reports(atributo *atributos, int quantidade) {
  FILE *reportFile = fopen(ATTACK_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Error creating %s\n", ATTACK_REPORT_FILE);
    exit(5);
  }

  // Assuming PKT_CLASS is the attribute representing attack type
  int i, j;
  char **attackTypes = (char **)malloc(quantidade * sizeof(char *));
  int *attackCounts = (int *)malloc(quantidade * sizeof(int));
  if (!attackTypes || !attackCounts) {
    fprintf(stderr, "Memory allocation error\n");
    exit(6);
  }

  for (i = 0; i < quantidade; i++) {
    attackTypes[i] = strdup(atributos[i].rotulo);
    attackCounts[i] = 0;
  }

  FILE *arff = fopen("netlog.arff", "r"); // Assuming you have the dataset in a file called netlog.arff
  if (!arff) {
    fprintf(stderr, "Unable to open netlog.arff\n");
    exit(7);
  }

  char line[2048];
  while (fgets(line, sizeof(line), arff)) {
    if (line[0] != '@') { // Assuming data lines start with non-@
      char *token = strtok(line, ",");
      if (token) {
        for (j = 0; j < quantidade; j++) {
          if (strcmp(token, attackTypes[j]) == 0) {
            // Assuming PKT_CLASS is the attribute representing attack type
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

  // Write the attack reports to R_ATAQUES.txt
  for (i = 0; i < quantidade; i++) {
    if (attackCounts[i] > 0) {
      fprintf(reportFile, "%s;%d\n", attackTypes[i], attackCounts[i]);
    }
    free(attackTypes[i]);
  }

  fclose(reportFile);
  fclose(arff);
  free(attackTypes);
  free(attackCounts);
}

// Function to generate entity reports
void generate_entity_reports(atributo *atributos, int quantidade) {
  FILE *reportFile = fopen(ENTITY_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Error creating %s\n", ENTITY_REPORT_FILE);
    exit(8);
  }

  // Assuming SRC_ADD is the attribute representing source IP addresses
  // Initialize counters for benign, potentially malicious, and malicious entities
  int benignCount = 0;
  int potentialMaliciousCount = 0;
  int maliciousCount = 0;

  FILE *arff = fopen("netlog.arff", "r"); // Assuming you have the dataset in a file called netlog.arff
  if (!arff) {
    fprintf(stderr, "Unable to open netlog.arff\n");
    exit(9);
  }

  char line[2048];
  while (fgets(line, sizeof(line), arff)) {
    if (line[0] != '@') { // Assuming data lines start with non-@
      char *token = strtok(line, ",");
      if (token) {
        // Assuming SRC_ADD is the attribute representing source IP addresses
        if (strcmp(atributos[0].rotulo, "SRC_ADD") == 0) {
          char *value = strtok(NULL, ",");
          if (value) {
            // Implement your logic to classify IP addresses here
            // For example, you can use a data structure to keep track of IP classifications
            // and update the counters accordingly.
            // Sample logic (replace with your own):
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

  // Write the entity reports to R_ENTIDADES.txt
  fprintf(reportFile, "Benign;%d\n", benignCount);
  fprintf(reportFile, "Potentially Malicious;%d\n", potentialMaliciousCount);
  fprintf(reportFile, "Malicious;%d\n", maliciousCount);

  fclose(reportFile);
  fclose(arff);
}

// Function to generate size reports
void generate_size_reports(atributo *atributos, int quantidade) {
  FILE *reportFile = fopen(SIZE_REPORT_FILE, "w");
  if (!reportFile) {
    fprintf(stderr, "Error creating %s\n", SIZE_REPORT_FILE);
    exit(10);
  }

  // Assuming PKT_CLASS is the attribute representing attack type
  // Assuming PKT_AVG_SIZE is the attribute representing the average packet size
  int i, j;
  char **attackTypes = (char **)malloc(quantidade * sizeof(char *));
  double *avgSizes = (double *)malloc(quantidade * sizeof(double));
  int *counters = (int *)malloc(quantidade * sizeof(int));
  if (!attackTypes || !avgSizes || !counters) {
    fprintf(stderr, "Memory allocation error\n");
    exit(11);
  }

  for (i = 0; i < quantidade; i++) {
    attackTypes[i] = strdup(atributos[i].rotulo);
    avgSizes[i] = 0.0;
    counters[i] = 0;
  }

  FILE *arff = fopen("netlog.arff", "r"); // Assuming you have the dataset in a file called netlog.arff
  if (!arff) {
    fprintf(stderr, "Unable to open netlog.arff\n");
    exit(12);
  }

  char line[2048];
  while (fgets(line, sizeof(line), arff)) {
    if (line[0] != '@') { // Assuming data lines start with non-@
      char *token = strtok(line, ",");
      if (token) {
        // Assuming PKT_CLASS is the attribute representing attack type
        // Assuming PKT_AVG_SIZE is the attribute representing the average packet size
        for (j = 0; j < quantidade; j++) {
          if (strcmp(token, attackTypes[j]) == 0) {
            char *value = strtok(NULL, ",");
            if (value) {
              // Assuming PKT_CLASS is the attribute representing attack type
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

  // Write the size reports to R_TAMANHO.txt
  for (i = 0; i < quantidade; i++) {
    if (counters[i] > 0) {
      double avgSize = avgSizes[i] / counters[i];
      fprintf(reportFile, "%s;%.2lf\n", attackTypes[i], avgSize);
    }
    free(attackTypes[i]);
  }

  fclose(reportFile);
  fclose(arff);
  free(attackTypes);
  free(avgSizes);
  free(counters);
}

// Function to generate a firewall configuration file
void generate_firewall_config(atributo *atributos, int quantidade) {
  FILE *configFile = fopen(FIREWALL_CONFIG_FILE, "w");
  if (!configFile) {
    fprintf(stderr, "Error creating %s\n", FIREWALL_CONFIG_FILE);
    exit(13);
  }

  char **maliciousIPs = (char **)malloc(quantidade * sizeof(char *));
  int maliciousCount = 0;

  FILE *arff = fopen("netlog.arff", "r"); // Assuming you have the dataset in a file called netlog.arff
  if (!arff) {
    fprintf(stderr, "Unable to open netlog.arff\n");
    exit(14);
  }

  char line[2048];
  while (fgets(line, sizeof(line), arff)) {
    if (line[0] != '@') { // Assuming data lines start with non-@
      char *token = strtok(line, ",");
      if (token) {
        // Assuming PKT_CLASS is the attribute representing attack type
        if (strcmp(atributos[0].rotulo, "PKT_CLASS") == 0) {
          char *value = strtok(NULL, ",");
          if (value && strcmp(value, "Normal") != 0) {
            // Assuming SRC_ADD is the attribute representing source IP addresses
            char *ipAddress = strtok(NULL, ",");
            if (ipAddress) {
              // Implement your logic to identify and store malicious IP addresses here
              // For example, add the IP address to the maliciousIPs array if it's considered malicious
              // Sample logic (replace with your own):
              if (isMalicious(value)) {
                maliciousIPs[maliciousCount++] = strdup(ipAddress);
              }
            }
          }
        }
      }
    }
  }

  // Write the malicious IP addresses to BLACKLIST.bl
  for (int i = 0; i < maliciousCount; i++) {
    fprintf(configFile, "%s\n", maliciousIPs[i]);
    free(maliciousIPs[i]);
  }

  fclose(configFile);
  fclose(arff);
  free(maliciousIPs);
}


