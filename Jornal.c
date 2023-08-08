#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noticia_t {
    char titulo[32];
    char texto[512];
    int idade;
} noticia_t;

typedef struct breakingNews_t {
    noticia_t noticia;
    struct breakingNews_t *prox;
} breakingNews_t;

typedef struct informe_t {
    noticia_t noticia;
    struct informe_t *prox;
} informe_t;

void requisita(char *titulo, char *texto) {
    getchar();
    printf("\nDigite o título: ");
    fgets(titulo, 32, stdin);
    printf("Digite o texto: ");
    fgets(texto, 512, stdin);
}

void mostrarEdicao(noticia_t *noticia1, noticia_t *noticia2) {
    printf("=======================================================\n");
    printf("< %s >\n", noticia1->titulo);
    printf("< %s >\n", noticia1->texto);
    printf("==\n");
    printf("< %s >\n", noticia2->titulo);
    printf("< %s >\n", noticia2->texto);
    printf("=======================================================\n");
}

void atualizarIdades(breakingNews_t *breakingNews, informe_t *informe) {
    breakingNews_t *bn = breakingNews;
    informe_t *inf = informe;

    while (bn != NULL) {
        bn->noticia.idade++;
        bn = bn->prox;
    }

    while (inf != NULL) {
        inf->noticia.idade++;
        inf = inf->prox;
    }
}

int main() {
    breakingNews_t *breakingNews = NULL;
    informe_t *informe = NULL;

    int op;

    do {
        printf("Entre um numero para (1) Cadastrar noticia, (2) Fechar Edicao, (3) Sair\n");
        scanf("%d", &op);

        if (op == 1) {
            int tipo;

            printf("Qual tipo de noticia voce deseja cadastrar? (0)Breaking News ou (1)Informe\n");
            scanf("%d", &tipo);

            noticia_t novaNoticia;
            requisita(novaNoticia.titulo, novaNoticia.texto);
            novaNoticia.idade = 0;

            if (tipo == 0) {
                breakingNews_t *novaBreakingNews = (breakingNews_t *)malloc(sizeof(breakingNews_t));
                novaBreakingNews->noticia = novaNoticia;
                novaBreakingNews->prox = breakingNews;
                breakingNews = novaBreakingNews;
            } else {
                informe_t *novoInforme = (informe_t *)malloc(sizeof(informe_t));
                novoInforme->noticia = novaNoticia;
                novoInforme->prox = informe;
                informe = novoInforme;
            }
        } else if (op == 2) {
            if (breakingNews != NULL && informe != NULL) {
                if (breakingNews->noticia.idade <= 3) {
                    breakingNews_t *noticia1 = breakingNews;
                    breakingNews = breakingNews->prox;

                    if (breakingNews->noticia.idade <= 3) {
                        breakingNews_t *noticia2 = breakingNews;
                        breakingNews = breakingNews->prox;

                        mostrarEdicao(&noticia1->noticia, &noticia2->noticia);
                        free(noticia1);
                        free(noticia2);
                    }
                }
                atualizarIdades(breakingNews, informe);
            } else {
                printf("Esta edicao foi pulada por falta de noticias!\n");
            }
        }
    } while (op != 3);

    while (breakingNews != NULL) {
        breakingNews_t *temp = breakingNews;
        breakingNews = breakingNews->prox;
        free(temp);
    }
    while (informe != NULL) {
        informe_t *temp = informe;
        informe = informe->prox;
        free(temp);
    }

    return 0;
}
