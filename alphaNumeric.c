#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define tam 10

void alpha(char* s) {
    int len = strlen(s);
    int newLen = 0;  // Acompanhe o novo comprimento da string modificada

    for (int i = 0; i < len; i++) {
        if (isalpha(s[i]) || isdigit(s[i])) {
            // guarda apenas caracteres alfabéticos e numéricos
            s[newLen++] = s[i];
        }
    }

    // termine a string modificada com o caractere nulo
    s[newLen] = '\0';
}

int main() {
    char str[tam];

    fgets(str, tam, stdin);

    alpha(str);

    puts(str);

    return 0;
}
