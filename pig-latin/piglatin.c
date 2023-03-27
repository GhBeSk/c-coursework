/**
 * @file piglatin.c
 * @brief Functions to convert a given text into Pig Latin.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pig.c"

#define MAX_LINE_LENGTH 1024

/**
 * @brief Main function for the Pig Latin translator.
 *
 * This program takes user input in the form of English text, tokenizes it into words,
 * translates each word into Pig Latin, and prints the translated words. The program
 * continues until the user inputs an empty line.
 *
 * @return 0 on successful execution.
 */

int main() {
    char input[MAX_LINE_LENGTH];
    char *word;
    char *translation;


    // Prompt the user for input
    printf("Enter a line of English text (empty line to exit):\n");

    // Read input until an empty line is encountered
    while (fgets(input, MAX_LINE_LENGTH, stdin) && input[0] != '\n') {
        // Remove newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Split the input into words using strtok
        word = strtok(input, " ");
        while (word != NULL) {
            // Translate the word to Pig Latin and print it
            translation = pig(word);
            printf("%s ", translation);
            free(translation);
            translation = NULL; // Set the pointer to NULL after freeing memory

            // Get the next word in the input
            word = strtok(NULL, " ");
        }

        printf("\n\nEnter another line of English text (empty line to exit):\n");
    }

    return 0;
}
