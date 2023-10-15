#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 1024

// Function to check if a character is a vowel
int isVowel(char c) {
    // Convert the character to lowercase to handle both cases
    c = tolower(c);

    // Check if it's one of the lowercase vowels
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
        return 1; // It's a vowel
    } else {
        return 0; // It's not a vowel
    }
}

int main() {
    char phrase[size];

    printf("enter phrase: ");

    // Read a line of text (including spaces) from the user
    fgets(phrase, size, stdin);

    int i = 0;

    // Iterate through the characters in the input string until '\0' or '\n' is encountered
    while (phrase[i] != '\0' && phrase[i] != '\n') {
        if (isVowel(phrase[i]) || phrase[i] == ' ') {
            // If the character is a vowel or a space, print it as is
            printf("%c", phrase[i]);
        } else {
            // If the character is a consonant, print it followed by "OP"
            printf("%cOP", phrase[i]);
        }

        i++;
    }

    printf("\n");

    return 0;
}
