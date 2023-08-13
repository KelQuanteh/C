#include <stdio.h>
#include <string.h>

#define tam 20

int busca(char* p, char* s) {
    int pLen = strlen(p);
    int sLen = strlen(s);

    if (pLen == 0 || sLen == 0)
        return -2;

    for (int i = 0; i <= pLen - sLen; i++) {
        int count = 0;
        for (int j = 0; j < sLen; j++) {
            if (p[i + j] == s[j])
                count++;
            else
                break; // Sair do loop se nenhuma correspondência for encontrada
        }
        if (count == sLen)
            return i; 
    }

    return -1; 
}

int main() {
    char primeiro[tam];
    char segundo[tam];

    printf("Digite a primeira string: ");
    fgets(primeiro, tam, stdin);
    printf("Digite a segunda string: ");
    fgets(segundo, tam, stdin);

    // Remover caracteres de nova linha da entrada
    primeiro[strcspn(primeiro, "\n")] = '\0';
    segundo[strcspn(segundo, "\n")] = '\0';

    int result = busca(primeiro, segundo);

    if (result != -1) {
        printf("A segunda string ocorre na primeira string a partir do índice: %d\n", result);
    } else {
        printf("A segunda string não foi encontrada na primeira string.\n");
    }

    return 0;
}
