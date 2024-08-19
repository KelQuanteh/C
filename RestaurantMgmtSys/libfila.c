#include "libfila.h"
#include <stdio.h>
#include <stdlib.h>

fila_t* fila_cria (){
    fila_t *f;
	
	if ( !(f = malloc(sizeof(fila_t))) )
		return NULL;
	f->ini = NULL;
	f->fim = NULL;
	f->tamanho = 0;
	return f;
}

fila_t* fila_destroi (fila_t* f){
    nodo_f_t *aux,*p;
	if ( !fila_vazia(f) ){
		p = f->ini;
		while (p->prox != NULL){
			aux = p->prox;
			free(p);
			p = aux;
		}
		free(p);
	}
	free(f);
    printf("fila destruído \n");

	return NULL;
}

int fila_vazia (fila_t* f){
    return f->tamanho==0;
}

int fila_tamanho (fila_t* f){
    return (f->tamanho);
}

int queue (fila_t* f, int elemento){
    nodo_f_t *novo;
	if ( !(novo = malloc(sizeof(nodo_f_t))) )
			return 0;
	novo->chave = elemento;
	if (fila_vazia(f))
                f->ini = novo;
	else
		f->fim->prox = novo;
	novo->prox = NULL;
	f->fim = novo;
	f->tamanho++;
	return 1;
}

int dequeue (fila_t* f, int* elemento){
    nodo_f_t *aux;	
	if (fila_vazia(f))
		return 0;	
	*elemento = f->ini->chave;
	aux = f->ini;
	f->ini = f->ini->prox;
	free(aux);
	f->tamanho--;
	return 1;
}

void fila_imprime (fila_t* f){
    nodo_f_t* temp = f->ini;
    while(temp != NULL){
        printf("%d ", temp->chave);
        temp = temp->prox;
    }
    printf("\n");
}