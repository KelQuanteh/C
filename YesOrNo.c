#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
char resp;

for (;;){
  printf ("Aceita? (s/n) ") ;
  resp = getchar() ;
  if(resp == 's' || resp == 'n')
    break;
  printf ("\n") ;
}

    return 0;
}