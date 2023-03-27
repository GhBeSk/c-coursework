/**
 * @file demo_shuffle.c
 * @brief A demonstration program to show the usage of riffle shuffle functions defined in riffle.c.
 */

#include <stdio.h>
#include "riffle.c"

/**
 * @brief Main function for demonstrating the riffle shuffle.
 *
 * This program shuffles an array of integers and an array of Greek letter names
 * using the riffle shuffle algorithm.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
    // Define the array of integers
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int len_numbers = sizeof(numbers) / sizeof(numbers[0]);

    // Define the array of Greek letter names
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta",
                     "eta", "theta", "iota", "kappa", "lambda", "mu"};
    int len_greek = sizeof(greek) / sizeof(greek[0]);

    // Print the original array of integers
    printf("Original array of integers:\n");
    for (int i = 0; i < len_numbers; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Shuffle the array of integers
    riffle(numbers, len_numbers, sizeof(int), 10);

    // Print the shuffled array of integers
    printf("Shuffled array of integers:\n");
    for (int i = 0; i < len_numbers; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // "Check shuffle result for integers" indicates whether the shuffle function maintains all elements
    // in the original array of integers. A value of 1 means that the shuffled array contains all the original elements
    printf("Integers shuffle test (1 = successful, 0 = failed): %d\n", check_shuffle(numbers, len_numbers, sizeof(int), cmp_int));

    // Print the original array of Greek letters
    printf("\nOriginal array of Greek letters:\n");
    for (int i = 0; i < len_greek; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n");

    // Shuffle the array of Greek letters
    riffle(greek, len_greek, sizeof(char *), 10);

    // Print the shuffled array of Greek letters
    printf("Shuffled array of Greek letters:\n");
    for (int i = 0; i < len_greek; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n");

    // "Check shuffle result for integers" indicates whether the shuffle function maintains all elements
    // in the original array of integers. A value of 1 means that the shuffled array contains all the original elements
    printf("Greek letters shuffle test (1 = successful, 0 = failed): %d\n", check_shuffle(greek, len_greek, sizeof(char *), cmp_string));

    return 0;
}
