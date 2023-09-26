#ifndef __ARFF__
#define __ARFF__

typedef struct {
  char *rotulo;
  char *tipo;
  char **categorias;
} atributo;

// arff.h
void exibe_atributos(atributo *infos, int quantidade);
int conta_atributos(FILE *arff);
void processa_categorias(atributo *elemento, char *categorias);
atributo* processa_atributos(FILE *arff, int quantidade);
void valida_arff(FILE *arff, atributo *atributos, int quantidade);
void generate_attack_reports(atributo *atributos, int quantidade);
void generate_entity_reports(atributo *atributos, int quantidade);
void generate_size_reports(atributo *atributos, int quantidade);
void generate_firewall_config(atributo *atributos, int quantidade);

#endif