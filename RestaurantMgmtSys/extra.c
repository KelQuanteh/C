#include <stdio.h>
#include <stdlib.h>
#include "extra.h"


pilha_t* ref_pilha(int r){
    pilha_t* ref = pilha_cria(r);
    for(int i=r; i>0; i--)
        push(ref, i);
    return ref;
}

pilha_t* mascara_pilha(int m){
    pilha_t* mascaras = pilha_cria(m);
    for(int i=m; i>0; i--)
        push(mascaras, i);
    return mascaras;
}

pessoa_t* pessoa_fila(){
    pessoa_t* pessoa= malloc(1000 * sizeof(pessoa_t));
    if(pessoa==NULL)
        return NULL;
    return pessoa;
}


void randomize_queue(pessoa_t* pessoa){
	int pV, pM, pD;
        for(int i= 0; i<1000; i++){
                pV= rand()%100;
                pM= rand()%100;
                pD= rand()%100;

                pessoa[i].ticket= i+1;
                pessoa[i].vacinado= pV<80 ?  1 : 0;
                pessoa[i].mascara = pM<80 ?  1 : 0;
                pessoa[i].dinheiro = pD<60 ?  1.3 : 3.8;
    	}
}

fila_t* atendimento_fila(){
    fila_t* fila= fila_cria();
    for(int i=0; i<1000; i++){
        queue(fila, i);
    }
    return fila;
}

void destroi_atendimento_fila(fila_t* fila_atendimento){
    fila_destroi(fila_atendimento);
    return;
}


record_t* cria_record(){
    record_t* rec= malloc(sizeof(record_t));
    if(rec== NULL)
        return NULL;        
    rec->total_rem= lista_cria();    
    rec->mascara_rem= lista_cria();
    rec->vac_rem= lista_cria();

    rec->totalRec= 0;
    rec->refRec= 0;
    rec->maskRec= 0;

    return rec;
}

int destroi_record(record_t* rec){
    lista_destroi(rec->total_rem);
    lista_destroi(rec->mascara_rem);
    lista_destroi(rec->vac_rem);

    free(rec);

    return 1;
}

void show_records(record_t* rec){
    printf("R$%.2f foi arrecadado no total\n", rec->totalRec);
    printf("\n");
    printf("R$%.0f rendeu a venda de mascaras\n", rec->maskRec/2.5);
    printf("\n");
    printf("$R%.0f foi para refeicoes\n", rec->refRec/1.3);
    printf("\n");
    printf("%d pessoas não foram vacinadas e foi recusada a admissão:\n", lista_tamanho(rec->vac_rem));
    printf("\n");
    lista_imprime(rec->vac_rem);
    printf("\n");
    printf("%d pessoas não puderam comprar máscaras e não comeu:\n", lista_tamanho(rec->mascara_rem));
    printf("\n");
    lista_imprime(rec->mascara_rem);
    printf("\n");
    printf("%d pessoas não comeram por outros motivos\n", lista_tamanho(rec->vac_rem)+lista_tamanho(rec->mascara_rem));
}

void libera_pessoas(pessoa_t* pessoa){
    free(pessoa);
    return;
}

int fiscalize(fila_t* fila_atendimento, pessoa_t* pessoa, pilha_t* mascaras, pilha_t* ref, record_t* rec){
    int removido;
    dequeue(fila_atendimento, &removido); 
    if(pilha_vazia(ref)){
        lista_insere_ordenado(rec->total_rem, pessoa[removido].ticket);
        return 0;
    }
    else if(!pessoa[removido].vacinado){
        lista_insere_ordenado(rec->total_rem, pessoa[removido].ticket);
        lista_insere_ordenado(rec->vac_rem, pessoa[removido].ticket);
        return 0;
    }
    else{
        if(!pessoa[removido].mascara){
            if(pilha_vazia(mascaras) || pessoa[removido].dinheiro < 3.8){
                lista_insere_ordenado(rec->total_rem, pessoa[removido].ticket);
                lista_insere_ordenado(rec->mascara_rem, pessoa[removido].ticket);
                return 0;
            }
            else{
                pessoa[removido].dinheiro -= 2.5;
                pessoa[removido].mascara = 1;
                rec->totalRec += 2.5;
                rec->maskRec += 2.5;
                pop(mascaras);
                queue(fila_atendimento, removido);
                return 0;
            }
        }
        pessoa[removido].dinheiro -= 1.3;
        rec->totalRec += 1.3;
        rec->refRec += 1.3;
        pop(ref);
    }
    return 1;
}
