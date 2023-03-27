/**
 * @file pig.c
 * @brief Main program to convert input text into Pig Latin using the functions defined in piglatin.c.
 */

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Check if a character is a vowel.
 *
 * @param c The character to be checked.
 * @return true if the character is a vowel, false otherwise.
 */
bool is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

/**
 * @brief Convert a word into Pig Latin.
 *
 * @param word The word to be converted.
 * @return A new string containing the Pig Latin translation.
 */
char *pig(char *word) {
    size_t len = strlen(word);
    // Allocate space for the result (including "ay" or "way" and null terminator)
    char *result = (char *)malloc(len + 4);

    int first_vowel_index = 0;

    // Find the index of the first vowel in the word
    while (word[first_vowel_index] != '\0' && !is_vowel(word[first_vowel_index]) && !(word[first_vowel_index] == 'y' && first_vowel_index > 0)) {
        first_vowel_index++;
    }

    if (first_vowel_index == 0) {
        // Rule 2: For words that begin with a vowel
        // Copy the original word and append "way" to the result
        strcpy(result, word);
        strcat(result, "way");
    } else {
        // Rule 1: For words that begin with consonants
        // Copy the part of the word starting from the first vowel to the result
        strncpy(result, &word[first_vowel_index], len - first_vowel_index);
        // Copy the consonants before the first vowel to the result
        strncpy(&result[len - first_vowel_index], word, first_vowel_index);
        // Append "ay" to the result
        strcpy(&result[len], "ay");
    }

    return result;
}

