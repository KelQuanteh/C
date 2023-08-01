#include <stdio.h>

int main(){
    int vet[5]= {2, 4, 6, 8, 10};
    int* p;

    p= vet; 

    printf("the value of *p is: %d \n", *p); //this will return vet[0]

    p+= 3;  //move the ointer three steps up 

    printf("the value of *p is: %d \n", *p);

    *p= 16; 

    for(int i=0; i<5; i++){
        printf("%d, \n", vet[i]);
    }
    return 0;
}