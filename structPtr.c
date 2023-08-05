#include <stdio.h> 

typedef struct tenants_t {
    char name[100];
    int floor; 
    int apt; 
} tenants; 

int main(){
    tenants *ptr; 

    tenants tenant = {"kelvin", 1, 112}; 

    ptr = &tenant;

    printf("the tenant is %s, lives on floor %d at apartment %d \n", tenant.name, tenant.floor, tenant.apt); 

    (*ptr).apt = 114;  

    printf("the tenant is %s, lives on floor %d at new apartment %d \n", tenant.name, tenant.floor, tenant.apt); 

    return 0; 
}