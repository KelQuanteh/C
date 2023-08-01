#include <stdio.h> 

int main(){
    int a= 100; 
    int* p;
    int** ptr; 

    p= &a; 
    ptr= &p; 

    printf("the value of *p is %d: \n", *p);
    printf("the value of **ptr is %d: \n", **ptr);

    **ptr= 67; 

    printf("the value of a is %d: \n", a);

    return 0;
}