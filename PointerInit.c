#include <stdio.h>

int main(){
    int a= 7; 
    int* p; 

    printf("the address of a is %p \n", &a);
    printf("the address of p is %p \n", p);

    p= &a; 
    printf("the value of p is %p \n", p);
    printf("the value of *p is %d \n", *p);

    *p= 88; 

    printf("the value of a is %d \n", a);


    return 0;
}