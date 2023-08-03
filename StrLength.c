#include <stdio.h>

int main() {
    char myString[100]; 

    printf("Enter a string: ");
    scanf("%s", myString);

    char* p= myString;
    int length = 0; 

    while (*p != '\0')
    {
        length++;
        p++;
    }
    
    printf("the length of your string is: %d \n", length);

    return 0;
}
