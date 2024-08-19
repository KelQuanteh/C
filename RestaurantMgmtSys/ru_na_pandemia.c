#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libfila.h"
#include "liblista.h"
#include "libpilha.h"
#include "extra.h"

int main(){
        int m= rand()%100;
        int r= rand()%1000;
        
        pilha_t* mascaras= mascara_pilha(m);
        pilha_t* ref= ref_pilha(r);
        pessoa_t* pessoa= pessoa_fila();

        randomize_queue(pessoa);
        
        fila_t* fila_atendimento= atendimento_fila();

        lista_t* nao_atendidos= lista_cria();

        lista_insere_ordenado(nao_atendidos, pessoa->ticket);

        record_t* rec= cria_record();
        
        while(!fila_vazia(fila_atendimento))
                fiscalize(fila_atendimento, pessoa, mascaras, ref, rec);
        show_records(rec);
        
        destroi_record(rec);
        destroi_atendimento_fila(fila_atendimento);
        libera_pessoas(pessoa);
        pilha_destroi(mascaras);
        pilha_destroi(ref);

        return 0;
}
