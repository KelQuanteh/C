#include <stdio.h> 
#include <string.h>

typedef struct noticia_t {
    char titulo[32];
    char texto[512];
    int  idade; 
} noticia_t;

typedef struct breakingNews_t {
    noticia_t noticia;
    struct breakingNews_t *prox ;
} breakingNews_t;

typedef struct informe_t {
    noticia_t noticia;
    struct informe_t *prox ;
} informe_t;

void requisita(char *titulo, char *texto){
    getchar();
    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

int main(){

    breakingNews_t* breakingNews;
    informe_t* informe;
    
    int op; 

    printf("Entre um numero para (1) Cadastrar noticia, (2) Fechar Edicao, (3)Sair \n");
    scanf("%d", &op);

    if(op == 1){
        int tipo;

        printf("Qual tipo de noticia voce deseja cadastrar? (0)Breaking News ou (1)Informe\n");
        scanf("%d", &tipo);

        if(tipo == 0){
            requisita(breakingNews->noticia.titulo, breakingNews->noticia.texto);
        } else {
            requisita(informe->noticia.titulo, informe->noticia.texto);
        }
    }else if (op == 2){

    } else 
        return 0;
}