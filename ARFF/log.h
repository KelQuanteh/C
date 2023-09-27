#ifndef __LOG__
#define __LOG__

#include "arff.h"  // Inclui o cabeçalho "arff.h" para usar tipos e estruturas definidos nele

// Protótipos das funções relacionadas ao processamento e geração de relatórios a partir de um arquivo ARFF

void valida_arff(FILE *arff, atributo *atributos, int quantidade);  // Valida um arquivo ARFF

void generate_attack_reports(atributo *atributos, int quantidade, FILE* file);  // Gera um relatório de ataques

void generate_entity_reports(atributo *atributos, int quantidade, FILE* file);  // Gera um relatório de entidades

void generate_size_reports(atributo *atributos, int quantidade, FILE* file);  // Gera um relatório de tamanhos

void generate_firewall_config(atributo *atributos, int quantidade, FILE* file);  // Gera uma configuração de firewall

#endif  // Fim da diretiva condicional de inclusão múltipla
