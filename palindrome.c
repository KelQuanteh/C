#include <stdio.h>
#include <string.h>

#define tam 20

int palindrome(char* s){
    int len = strlen(s) - 1;

    int count = 0; 

    for (int i = 0; i < len/2; i++)
    {
        if (s[i] == s[len - i - 1])
            count++;
        else
            break;
    }
    
    if (count == len/2)
        return 1;
    else
        return 0;    
}

int main() {
    char str[tam];
    fgets(str, tam, stdin);
    printf("%d \n", palindrome(str));

    return 0; 
}
