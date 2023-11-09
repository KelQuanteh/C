#include <stdio.h> 
#include "hello.h"

int main(){
    int lang; 
    
    printf("english(1), french(2), portuguese(3): ");
    scanf("%d", &lang); 

    if(lang == 1)
        hello_eng();
    else if(lang == 2)
        hello_fr();
    else if(lang == 3)
        hello_pt();

    return 0; 
}