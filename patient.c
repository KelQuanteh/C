#include <stdio.h> 
#include <string.h> 

typedef struct patient_t
{
    char name[100]; 
    short age; 
    short room; 
} patient;

void imprimePatient(patient p){
    printf("This is %s, aged %d in room %d \n", p.name, p.age, p.room);
}

patient nullPatient(){
    patient p= {"null", 0, 0}; 
    return(p); 
}

int main(){
    patient a = {"Melvin", 24, 13}; 

    patient b = a; 
    imprimePatient(b); 

    a = nullPatient();
    imprimePatient(a);

    return 0; 
}