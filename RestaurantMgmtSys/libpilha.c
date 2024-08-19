#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"


pilha_t* pilha_cria(int nelem){ 
    pilha_t * pilha = (pilha_t*) malloc(sizeof(pilha_t));
    
    if(pilha==NULL)
        return NULL;   
    pilha->elems=(int*) malloc(nelem * sizeof(int));
    pilha->nelem= nelem;
    pilha->topo=-1;
    return pilha;
}

int push (pilha_t* pilha, int elem){
    if (pilha->topo >= pilha->nelem - 1){
        printf("Estouro de pilha \n");
    } 
    else{    
        pilha->topo = pilha->topo + 1;
        pilha->elems[pilha->topo] = elem;
    }

    return 0;
}

int pop (pilha_t* pilha){
    if (pilha_vazia(pilha)){
        printf("A pilha está vazia \n");
    } 
    else{
        printf("Elemento que é removido é %d \n",pilha->elems[pilha->topo]);
        pilha->topo --;
    }
    return 0;
}

int pilha_topo (pilha_t* pilha){
    if(!pilha_vazia(pilha))
        printf("%d \n", pilha->topo);
    return 0;
}

int pilha_vazia (pilha_t* pilha){
    return pilha->topo==0;
}

int pilha_tamanho (pilha_t* pilha){
    if(!pilha_vazia(pilha))
        printf("%d \n", pilha->nelem);
    return 0;
}

pilha_t* pilha_destroi (pilha_t* pilha){
    free(pilha);
    printf("a pilha está vazia \n");
    return 0;
}

void pilha_imprime (pilha_t* pilha){
    int i =0;
    while(i < pilha->nelem){                
        printf("%d: %d, ", i, pilha->elems[i]);   
        i++;
    }
    printf("\n");
}
