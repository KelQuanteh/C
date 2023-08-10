#include <stdio.h>
#include <string.h>

void reverse(char* s){
    char c[10];
    int j = strlen(s);
    for (int i = 0; i < strlen(s); i++)
    {
        c[i] = s[j-1];
        j--;
    }

    c[strlen(s)] = '\0';
    strcpy(s, c);
}

int main(){
    char str[10]; 

    printf("entre uma palavra: ");
    fgets(str, 10, stdin);
    
    reverse(str);
    
    puts(str);
    
    return 0;
}