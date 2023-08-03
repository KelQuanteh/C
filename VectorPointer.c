#include <stdio.h>

int main(){
    int vet[10];
    int* p; 

    p= vet; 
    
    int count= 0; 

    while(count< 10){
        scanf("%d", &*p);
        count++;
        p++;
    }

    count= 9;
    p= &vet[9];

    while (count> -1)
    {
        printf("%d ", *p);   
        count--;
        p--;
    }

    printf("\n");
    
    return 0;
}