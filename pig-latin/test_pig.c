/**
 * @file test_pig.c
 * @brief Test program to check the correctness of the Pig Latin conversion functions defined in piglatin.c.
 */

#include <stdio.h>
#include "pig.c"

/**
 * @brief Test the pig() function with a word and expected Pig Latin translation.
 *
 * @param word The input word to test.
 * @param expected The expected Pig Latin translation of the input word.
 */
void test_pig(char *word, char *expected) {
    char *result = pig(word);
    printf("%s => %s\n", word, result);

    // Check if the returned result matches the expected translation
    if (strcmp(result, expected) != 0) {
        printf("Test failed: expected %s, got %s\n", expected, result);
    }

    free(result);
    result = NULL; // Set the pointer to NULL after freeing memory
}

/**
 * @brief Main function for the test program.
 * 
 * Runs a series of test cases for the Pig Latin translation function and outputs the results.
 * 
 * @return 0 upon successful execution.
 */
int main() {
    test_pig("happy", "appyhay");
    test_pig("duck", "uckday");
    test_pig("glove", "oveglay");
    test_pig("evil", "evilway");
    test_pig("eight", "eightway");
    test_pig("yowler", "owleryay");
    test_pig("crystal", "ystalcray");
    return 0;
}
