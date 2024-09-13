#include "liblista.h"
#include <stdlib.h>
#include <stdio.h>

lista_t* lista_cria (){
    lista_t* l = malloc(sizeof(lista_t));
    
    if(l==NULL)
        return NULL;

    l->ini = NULL;
    l->tamanho = 0;
    return l;
}

lista_t* lista_destroi (lista_t* l){
    nodo_l_t* aux1;
    nodo_l_t* aux2;    
    aux1 = l->ini;
    if(aux1 == NULL){ 
        free(l);
        return NULL;
    }    
    aux2 = l->ini->prox;
    while(aux2!=NULL){
        free(aux1);
        aux1 = aux2;
        aux2 = aux2->prox;
    }
    free(aux1);
    free(l);
    return NULL;
}

int lista_vazia (lista_t* l){
    if(l->tamanho == 0)
        return 1;
    return 0;
}

int lista_tamanho (lista_t* l){
    return l->tamanho;
}

int lista_insere_inicio (lista_t* l, int elemento){
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    if(nodo==NULL)
        return 0;    
    nodo->prox = l->ini;
    nodo->elemento = elemento;
    l->ini = nodo;
    l->tamanho++;
    return 1;
}

int lista_insere_fim (lista_t* l, int elemento){    
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    nodo_l_t* nodoAux;
    if(nodo==NULL)
        return 0;
    nodo->prox = NULL;
    nodo->elemento = elemento;    
    if(lista_vazia(l)){
        l->ini = nodo;
        l->tamanho++;
        return 1;
    }    
    nodoAux = l->ini;
    while(nodoAux->prox!=NULL){
        nodoAux = nodoAux->prox;
    } 
    nodoAux->prox = nodo;
    l->tamanho++;
    return 1;
}

int lista_insere_ordenado (lista_t* l, int elemento){
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    nodo_l_t* nodoAux;
    if(nodo==NULL)
        return 0;    
    nodo->elemento = elemento;
    nodo->prox = NULL;    
    if(lista_vazia(l)){
        lista_insere_inicio(l, elemento);
        free(nodo);
        return 1;
    }
    nodoAux = l->ini;    
    if(nodoAux->elemento >= elemento){
        lista_insere_inicio(l, elemento);
        free(nodo);
        return 1;
    }
    while(nodoAux->prox!=NULL){ 
        if(nodoAux->prox->elemento > elemento){
            break;
        }
        nodoAux = nodoAux->prox;
    }
    if(nodoAux->prox==NULL){
        free(nodo);
        lista_insere_fim(l, elemento);
        return 1;
    }
    nodo->prox = nodoAux->prox;
    nodoAux->prox = nodo;
    l->tamanho++;
    return 1;
}

int lista_retira_inicio (lista_t* l, int* elemento){
    nodo_l_t* aux;
    if(lista_vazia(l)) 
        return 0;    
    aux = l->ini;
    *elemento = l->ini->elemento;
    l->ini = l->ini->prox;
    l->tamanho--;
    free(aux);
    return 1;
}

int lista_retira_fim (lista_t* l, int* elemento){
    nodo_l_t* aux;
    nodo_l_t* liberarAux;
    if(lista_vazia(l))
        return 0;
    if(lista_tamanho(l) == 1){
        *elemento = l->ini->elemento;
        lista_retira_inicio(l, elemento);
        return 1;
    }
    else{
        aux = l->ini;
        while(aux->prox->prox != NULL){
            aux = aux->prox;
        }
        liberarAux = aux->prox; 
        *elemento = aux->prox->elemento;
        aux->prox = NULL;
        free(liberarAux);
        l->tamanho--;
    }
    return 1;
}

int lista_retira_elemento (lista_t *l, int elemento){
    nodo_l_t* aux;
    nodo_l_t* liberarAux;
    if(lista_vazia(l))
        return 0;
    if(lista_tamanho(l) == 1){
        if(l->ini->elemento == elemento){
            free(l->ini);
            l->ini = NULL;
            l->tamanho--;
            return 1;
        }
        else
            return 0;
    }
    else{ 
        if(l->ini->elemento == elemento){
            liberarAux = l->ini;
            l->ini = l->ini->prox;
            l->tamanho--;
            free(liberarAux);
            return 1;
        }
        aux = l->ini;
        while(aux->prox->prox != NULL){
            if(aux->prox->elemento == elemento){
                liberarAux = aux->prox;
                aux->prox = aux->prox->prox;
                l->tamanho--;
                free(liberarAux);
                return 1;
            }
            aux = aux->prox;
        }
        if(aux->prox->elemento == elemento){
                liberarAux = aux->prox; 
                aux->prox = NULL;
                l->tamanho--;
                free(liberarAux);
                return 1;
        }
    }
    return 0;
}

int lista_pertence (lista_t* l, int elemento){
    nodo_l_t* aux;
    if(lista_vazia(l))
        return 0;
    aux = l->ini;
    while(aux->prox != NULL){
        if(aux->elemento == elemento)
            return 1;
        aux = aux->prox;
    }
    if(aux->elemento == elemento)
        return 1;
    return 0;
}

void lista_imprime (lista_t* l){
    nodo_l_t* n;
    if(lista_vazia(l))
            return;
    
    n = l->ini;
    while(n->prox != NULL){
        printf("%d\n ", n->elemento);
        n = n->prox;
    }
    printf("%d\n", n->elemento);
    return; 
}
