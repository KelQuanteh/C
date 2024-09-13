#ifndef _Extra_t_H
#define _Extra_t_H
#include "libfila.h"
#include "liblista.h"
#include "libpilha.h"


struct pessoa {
        int ticket;
        int vacinado;
        int mascara;
        double dinheiro;
};
typedef struct pessoa pessoa_t;

struct record {
    double totalRec;
    int refRec;
    int maskRec;

    lista_t* total_rem;
    lista_t* vac_rem;
    lista_t* mascara_rem;
};
typedef struct record record_t;


/* Cria e retorna uma nova pilha de refeicoes */
pilha_t* ref_pilha(int r);

/* Cria e retorna uma nova pilha de mascaras */
pilha_t* mascara_pilha(int m);

/* Cria uma fila de pessoas */
pessoa_t* pessoa_fila();

/* Randomize as propriedades das pessoas na fila */
void randomize_queue(pessoa_t* pessoa);

/* Cria uma fila vazia de atendimentos */
fila_t* atendimento_fila();

/* Destrói o fila de pessoas atendidas */
void destroi_atendimento_fila(fila_t* fila_atendimento);

/* Limpa o cadastro de pessoas */
void libera_pessoas(pessoa_t* pessoa);

/* Cria um registro de atendidos */
record_t* cria_record();

int fiscalize(fila_t* fila_atendimento, pessoa_t* pessoa, pilha_t* mascaras, pilha_t* ref, record_t* rec);

/* Exibe o registro de atendidos */
void show_records(record_t* rec);

/* Destrói o registro */
int destroi_record(record_t* rec);


#endif
