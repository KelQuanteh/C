#include <stdio.h> 
#include <string.h>

#define tam 10

typedef struct alunos_t
{
  char nome[100]; 
  int idade; 
  long grr; 
  char curso[100]; 
} alunos;

void initVect(alunos s[], int size){
    for (int i = 0; i < size; i++){
        strcpy(s[i].nome, ""); 
        s[i].idade = 0; 
        s[i].grr = 0;
        strcpy(s[i].curso, "");  
    }
}

void lerAluno(alunos s[], int i){
    printf("Entre com os dados do aluno (nome, idade, grr, curso): ");
    scanf("%99s %d %ld %99s", s[i].nome, &s[i].idade, &s[i].grr, s[i].curso);
}

void imprimeAluno(alunos s[], int i){
    printf("Os dados do aluno %d são: ", i);
    printf("%s, %d, %ld, %s\n", s[i].nome, s[i].idade, s[i].grr, s[i].curso);
}

void imprimeAlunos(alunos s[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(s[i].nome, "") != 0) {
            printf("Os dados do aluno %d são: ", i);
            printf("%s, %d, %ld, %s\n", s[i].nome, s[i].idade, s[i].grr, s[i].curso);
        }
    }
}

void maisVinteDois(alunos s[], int size){
    for (int i = 0; i < size; i++) {
        if (s[i].idade > 22) {
            printf("%s\n", s[i].nome);
        }
    }
}

int main() {
    alunos students[tam];
    initVect(students, tam);

    char resp = 'y';

    while (resp != 'n') {
    int pos;
    printf("entre a pos onde quer colocar o aluno: ");
    scanf("%d", &pos);

    getchar(); 

    if (pos >= 0 && pos < tam) {
        lerAluno(students, pos);
    } else {
        printf("Posição inválida. Insira um valor entre 0 e %d.\n", tam - 1);
    }

    printf("Quer adicionar mais um aluno? (y/n) ");
    scanf(" %c", &resp);
}


    char resp2 = 'y';

    while (resp2 != 'n') {
        int pos;
        printf("entre a pos do aluno que voce quer: ");
        scanf("%d", &pos);

        getchar(); 
        
        if (pos >= 0 && pos < tam) {
            imprimeAluno(students, pos);
        } else {
            printf("Posição inválida. Insira um valor entre 0 e %d.\n", tam - 1);
        }

        printf("Quer ver mais um aluno? (y/n) ");
        scanf(" %c", &resp2);
    }

    imprimeAlunos(students, tam);
    maisVinteDois(students, tam);

    return 0;
}
