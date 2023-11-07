#include <stdlib.h>

#include "space.h"
#include "enemy.h"

// Função que gera um novo tabuleiro com base nas dimensões especificadas.
// O tabuleiro tem bordas, portanto, seu tamanho real é (max_x + 2) x (max_y + 2).
// Isso ocorre porque os índices variam de 0 a max_x + 1 e de 0 a max_y + 1.
space* generate_board(int max_y, int max_x){
    space *new_board = (space*) malloc (sizeof(space));
    new_board->map = (sqm**) malloc ((max_y + 1) * sizeof(sqm*));
    for (int i = 0; i <= max_y; i++) 
        new_board->map[i] = (sqm*) calloc (max_x + 1, sizeof(sqm));
    new_board->max_x = max_x;
    new_board->max_y = max_y;
    return new_board;
}

// Função que cria um novo tabuleiro com base nas dimensões especificadas
// e inicializa com inimigos nas linhas especificadas.
space* create_board(int max_y, int max_x, int enemy_lines) {
    if (max_x <= 0 || max_y <= 0 || enemy_lines > max_y) {
        return NULL;  // Parâmetros de entrada inválidos
    }

    space *board = (space*)malloc(sizeof(space*));
    if (board == NULL) {
        return NULL;  // Falha na alocação de memória
    }

    board->max_x = max_x;
    board->max_y = max_y;
    board->map = (sqm**)malloc((max_y + 1) * sizeof(sqm*));
    if (board->map == NULL) {
        free(board);
        return NULL;  // Falha na alocação de memória
    }

    for (int i = 0; i <= max_y; i++) {
        board->map[i] = (sqm*)malloc((max_x + 1) * sizeof(sqm));
        if (board->map[i] == NULL) {
            // Falha na alocação de memória, limpe e retorne NULL
            clean_board(board);
            return NULL;
        }
    }

    // Inicializa o tabuleiro adicionando inimigos nas linhas especificadas
    for (int i = 0; i <= enemy_lines; i++) {
        for (int j = 0; j <= max_x; j++) {
            if (!add_enemy(board, i, j)) {
                // Lida com erros, como falha na alocação de memória
                clean_board(board);
                return NULL;
            }
        }
    }

    return board;
}

// Função que libera a memória alocada para um tabuleiro,
// garantindo que todos os inimigos sejam devidamente desalocados.
void clean_board(space *board){
    for (int i = 0; i <= board->max_y; i++){
        for (int j = 0; j <= board->max_x; j++){
            if (!board->map[i][j].entity) continue;
            free(board->map[i][j].entity);
            board->map[i][j].entity = NULL;
        }
    }
}

// Função que destrói um tabuleiro, liberando toda a memória alocada.
void destroy_board(space* board){
    for (int i = 0; i <= board->max_y; i++)
        free(board->map[i]);
    free(board->map);
    free(board);
}
