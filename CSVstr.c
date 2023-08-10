#include <stdio.h>
#include <string.h>

int main(){
    char str[100];
    char col[100]; 

    fgets(str, 100, stdin);

    strcpy(col, str);
    
    char* token = strtok(col, ",");
    int i = 1;

    while (token != NULL) {
        printf("Coluna (%d): %s\n", i, token);
        token = strtok(NULL, ",");
        i++;
    }

    return 0;
}