#include <stdio.h>
#include <string.h>

void minimize(char* s){
    for(int i= 0; i< strlen(s); i++){
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
    }
}

int main(){
    char str[20];

    fgets(str, 20, stdin);
    str[strlen(str) -1] = '\0';

    minimize(str);

    puts(str);

    return 0;
}