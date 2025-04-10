#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n; 
    
    scanf("%d", &n); 
    
    int* v = malloc(n * sizeof(int));
    int soma = 0; 
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        soma = soma + v[i];  
    } 
    
    printf("%d", soma); 
    
    free(v);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
