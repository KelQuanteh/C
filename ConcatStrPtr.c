#include <stdio.h>
#include <string.h>

int main(){
    char firstString[100];
    char secondString[100];

    printf("Enter the first string: ");
    scanf("%s", firstString);

    printf("Enter the second string: ");
    scanf("%s", secondString);

    int firstLength = strlen(firstString);
    int secondLength = strlen(secondString);

    char concatStr[100]; 

    char* first= firstString; 
    char* second= secondString; 
    char* newString= concatStr; 
 

    while (*first != '\0')
    {
        *newString= *first; 
        first++;
        newString++;
    }

    while (*second != '\0')
    {
        *newString= *second; 
        second++;
        newString++;
    }
    
    printf("%s", concatStr);
    printf("\n");

    return 0; 
}