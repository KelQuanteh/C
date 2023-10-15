#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define size 1024

int main(){
    char phrase[size]; 

    printf("enter phrase: ");

    fgets(phrase, size, stdin); 

    puts(phrase); 
    
    return 0;
}