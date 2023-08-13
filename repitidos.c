#include <stdio.h>
#include <string.h>

#define tam 20

void remRep(char* s){
    int len = strlen(s);
    int newLen = 0;  // Acompanhe o novo comprimento da string modificada

    for (int i = 0; i < len; i++) {
        if (s[i] != s[i+1]) {
            // guarda apenas caracteres não repitidos
            s[newLen++] = s[i];
        }
    }

    // termine a string modificada com o caractere nulo
    s[newLen] = '\0';
}

int main(){
    char str[tam];
    fgets(str, tam, stdin);
    remRep(str); //remover caracteres repetidos
    puts(str);

    return 0;
}