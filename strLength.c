#include <stdio.h>
#include <string.h>

int length(char* s){
    int i = 1;
    int count = 0;
    while (s[i] != '\0')
    {
        count++;
        i++;
    }
    return count;
}

int main(){
    char str[10];

    fgets(str, 10, stdin);

    int l = length(str);

    printf("%d \n", l);

    return 0;
}