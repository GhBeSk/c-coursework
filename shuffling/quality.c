/**
 * @file quality.c
 * @brief Program that computes the average quality of riffle shuffles and finds the optimal number of shuffles needed to properly shuffle a list of length 50.
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "riffle.c"

/**
 * @brief Main function that computes the average quality of shuffles for a list of length 50 and prints the results to a file named "quality.txt".
 * 
 * @return int 0 if the program runs successfully, 1 if there is an error opening the output file.
 */

int main() {
    int N = 50;
    int shuffles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int len_shuffles = sizeof(shuffles) / sizeof(shuffles[0]);
    int trials = 30;
    float target_quality = 0.5;
    int optimal_shuffles = 0;
    float min_diff = 1.0;

     // Open the output file
    FILE *file = fopen("quality.txt", "w");
    if (file == NULL) {
        printf("Error opening quality.txt for writing.\n");
        return 1;
    }

    // Write the header of the output file
    fprintf(file, "Shuffles\tAverage Quality\n");
    fprintf(file, "----------------------------\n");

    // Calculate the average quality for each number of shuffles
    for (int i = 0; i < len_shuffles; i++) {
        float avg_quality = average_quality(N, shuffles[i], trials);
        fprintf(file, "%d\t\t%f\n", shuffles[i], avg_quality);

        float diff = fabs(avg_quality - target_quality);
        if (diff < min_diff) {
            min_diff = diff;
            optimal_shuffles = shuffles[i];
        }
    }

    // Write the conclusion and explanation to the output file
    fprintf(file, "\nBased on the results, %d shuffles are needed to properly shuffle a list of length 50.\n", optimal_shuffles);
    fprintf(file, "The average quality is computed over 30 trials to obtain more reliable results. The optimal number of shuffles needed to properly shuffle a list of length 50 is determined by finding the average quality closest to 0.5. It is important to note that the results may vary between different runs due to the randomness involved in the shuffling process. However, the program should generally give you a good estimate of the number of shuffles needed to properly shuffle a list of length 50 based on the average quality closest to 0.5.\n");
    
    // Close the output file
    fclose(file);

    printf("Output written to quality.txt\n");

    return 0;
}



