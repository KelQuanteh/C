#include <stdio.h>
#include <string.h>

void funcao1 (){
    printf("Hello World\n");
}

void funcao2(){
    printf("Olá Mundo!\n");
}

void falar(char *personagem, void (*mensagem)()){
    printf("%s, ", personagem);
    mensagem();
}


int main(int argc, char** argv) {
    char language[10] = "en";
    if (!strcmp("pt-br", language)) 
        falar(argv[1], funcao2);
    else if (!strcmp("en", language)) 
        falar(argv[1], funcao1);
    else printf("????\n");

    return 0; 
}