#ifndef __SPACE__
#define __SPACE__

// Definição da estrutura 'sqm' que representa uma unidade no espaço do jogo.
// Ela contém um ponteiro 'entity' que pode apontar para diferentes tipos de elementos,
// como inimigos, obstáculos ou a nave.
typedef struct {
    void *entity;
    enum {ENEMY, OBSTACLE, SHIP} type;  // Enumeração para identificar o tipo da entidade.
} sqm;

// Definição da estrutura 'space' que representa o espaço do jogo.
// Ela mantém uma matriz ('map') de unidades 'sqm' e as dimensões máximas do espaço em 'max_x' e 'max_y'.
typedef struct {
    sqm **map;
    int max_x;
    int max_y;
} space;

// Função para criar um espaço de jogo com as dimensões especificadas.
// 'max_y' e 'max_x' definem o tamanho do espaço, e 'enemy_lines' é o número de linhas de inimigos.
space* create_board(int max_y, int max_x, int enemy_lines);

// Função para limpar o espaço de jogo, liberando a memória alocada para suas unidades.
void clean_board(space *board);

// Função para destruir o espaço de jogo completamente, incluindo a matriz de unidades.
void destroy_board(space *board);

#endif
