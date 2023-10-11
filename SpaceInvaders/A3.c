#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "enemy.h"

// Função para verificar se uma string representa um número natural
char is_nat(char *string){
    for (int i = 0; string[i]; i++) 
        if (!isdigit(string[i])) 
            return 0;
    return 1; 
}

// Função para atualizar o relatório com informações sobre o jogo
void update_report(FILE *report, space *board, shot_sentinel *list, int r){
    // Cabeçalho do relatório para a rodada atual
    fprintf(report, "============= RODADA %d =============\n=> MAPA:\n", r);
    for (int i = 1; i <= board->max_y; i++){
        for (int j = 1; j <= board->max_x; j++){
            // Verifica se há uma entidade no quadrado do mapa
            if (board->map[i][j].entity)
                fprintf(report, "| E "); // Representa uma entidade no relatório
            else
                fprintf(report, "| 0 "); // Representa espaço vazio no relatório
        }
        fprintf(report, "|\n"); // Nova linha para cada linha do mapa
    }
    fprintf(report, "\n=> TIROS:\n");
    for (shot *i = (shot*) list->first; i; i = (shot*) i->next) 
        // Informações sobre os tiros no relatório
        fprintf(report, " - x: %u, y: %u\n", i->position_x, i->position_y);
    fprintf(report, "\n====================================\n\n"); // Fim da rodada no relatório
}

// Função para executar os eventos do jogo
void execute_event(space *board, shot_sentinel *list) {
    update_shots(board, list);

    for (int i = 1; i <= board->max_y; i++) {
        for (int j = 1; j <= board->max_x; j++) {
            if (board->map[i][j].entity && board->map[i][j].type == ENEMY) {
                enemy *shooter = board->map[i][j].entity;

                int canShoot = 1;

                for (int k = j + 1; k <= board->max_x; k++) {
                    if (board->map[i][k].entity) {
                        canShoot = 0;
                        break;
                    }
                }

                if (canShoot) {
                    straight_shoot(board, list, shooter); // Função para realizar disparos
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    int opt;
    int x = -1;
    int y = -1;
    int e = -1;
    int r = -1;
    char *o = NULL;

    opt = getopt(argc, argv, "x:y:e:r:o:");
    if (opt == -1) {
        fprintf(stderr, "Uso: ./space_enemies -x limite_x_mapa -y limite_y_mapa -e linhas_inimigos -r rodadas -o saida\n");
        return 1;
    }

    do {
        switch (opt) {
            case 'x':
                if (is_nat(optarg)) x = atoi(optarg);
                else {
                    fprintf(stderr, "Erro: Número inválido de colunas!\n");
                    return 2;
                }
                break;
            case 'y':
                if (is_nat(optarg)) y = atoi(optarg);
                else {
                    fprintf(stderr, "Erro: Número inválido de linhas!\n");
                    return 3;
                }
                break;
            case 'e':
                if (is_nat(optarg)) e = atoi(optarg);
                else {
                    fprintf(stderr, "Erro: Número inválido de linhas de inimigos!\n");
                    return 4;
                }
                break;
            case 'r':
                if (is_nat(optarg)) r = atoi(optarg);
                else {
                    fprintf(stderr, "Erro: Número inválido de rodadas!\n");
                    return 5;
                }
                break;
            case 'o':
                o = strdup(optarg);
                if (o == NULL) {
                    fprintf(stderr, "Erro: Falha na alocação de memória para 'o'!\n");
                    return 6;
                }
                break;
            default:
                fprintf(stderr, "Uso: ./space_enemies -x limite_x_mapa -y limite_y_mapa -e linhas_inimigos -r rodadas -o saida\n");
                return 1;
        }
    } while ((opt = getopt(argc, argv, "x:y:e:r:o:")) != -1);

    if (x == -1 || y == -1 || e == -1 || r == -1 || o == NULL) {
        fprintf(stderr, "Erro: Argumentos obrigatórios ausentes!\n");
        return 7;
    }

    FILE *report = fopen(o, "w+");
    if (report == NULL) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo de saída!\n");
        free(o);
        return 8;
    }

    space *board = create_board(y, x, e);
    if (board == NULL) {
        fprintf(stderr, "Erro: Falha ao criar o mapa!\n");
        free(o);
        fclose(report);
        return 9;
    }

    shot_sentinel* shot_list = create_shotlist();
    if (shot_list == NULL) {
        fprintf(stderr, "Erro: Falha ao criar a lista de tiros!\n");
        free(o);
        fclose(report);
        clean_board(board);
        destroy_board(board);
        return 10;
    }

    for (int t = 0; t < r; t++) {
        execute_event(board, shot_list);
        update_report(report, board, shot_list, t);
    }

    clean_board(board);
    destroy_board(board);
    clean_shots(shot_list);
    free(shot_list);
    free(o);
    fclose(report);

    return 0;
}
