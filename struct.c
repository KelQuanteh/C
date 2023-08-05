#include <stdio.h> 
#include <string.h>

typedef struct student_t { 
    int age; 
    char sex[7]; 
} student; 


int main(){
    student Melvin, Olivia; 

    Melvin.age = 24; 
    strcpy(Melvin.sex, "male");  

    Olivia.age = 20; 
    strcpy(Olivia.sex, "female"); 

    printf("the first student is Melvin, a %s aged %d \n", Melvin.sex, Melvin.age); 
    printf("the first student is Olivia, a %s aged %d \n", Olivia.sex, Olivia.age); 

    return 0; 
}