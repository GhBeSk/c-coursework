/**
 * @file riffle.c
 * @brief This file contains functions to perform riffle shuffle on arrays and evaluate the quality of the shuffle.
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Perform a single riffle shuffle of the array L.
 *
 * @param L The array to be shuffled.
 * @param len The length of the array.
 * @param size The size of each element in the array.
 * @param work A workspace array with the same size as L.
 */
void riffle_once(void *L, int len, int size, void *work) {
    int mid = len / 2;
    unsigned char *src = (unsigned char *)L;
    unsigned char *dst = (unsigned char *)work;

    srand(time(NULL));

    int i = 0, j = mid * size;
    for (int k = 0; k < len; k++) {
        // Choose from the first half or second half of the array based on 'choose'
        int choose = rand() % 2;

        // Perform a riffle shuffle by interleaving elements from src into dst
        if (choose == 0 && i < mid * size) {
            memcpy(dst, src + i, size);
            i += size;
        } else if (j < len * size) {
            memcpy(dst, src + j, size);
            j += size;
        } else {
            memcpy(dst, src + i, size);
            i += size;
        }
        dst += size;
    }

    // Copy shuffled elements from work back to L
    memcpy(L, work, len * size);
}

/**
 * @brief Shuffle the array L using N successive riffles.
 *
 * @param L The array to be shuffled.
 * @param len The length of the array.
 * @param size The size of each element in the array.
 * @param N The number of riffle shuffles to perform.
 */
void riffle(void *L, int len, int size, int N) {
    void *work = NULL; // Initialize the pointer to NULL
    work = malloc(len * size); // Allocate memory for the workspace array
    if (work == NULL) {
        return;
    }

    for (int i = 0; i < N; i++) {
        riffle_once(L, len, size, work);
    }

    free(work);
}

/**
 * @brief Compare two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return int Comparison result.
 */
int cmp_int(void *a, void *b) {
    int *x = (int *)a;
    int *y = (int *)b;

    if (*x > *y) return 1;
    if (*x < *y) return -1;
    return 0;
}

/**
 * @brief Compare two strings.
 *
 * @param a First string.
 * @param b Second string.
 * @return int Comparison result.
 */
int cmp_string(void *a, void *b) {
    char **x = (char **)a;
    char **y = (char **)b;

    return strcmp(*x, *y);
}

/**
 * @brief Check whether the riffle function respects the shuffle conditions.
 *
 * @param L The array to be checked.
 * @param len The length of the array.
 * @param size The size of each element in the array.
 * @param cmp Comparison function for the elements in the array.
 * @return int 1 if the shuffle conditions are respected, 0 otherwise.
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)) {
    void *original = NULL; // Initialize the pointer to NULL
    original = malloc(len * size);
    memcpy(original, L, len * size);
    
    void *shuffled = NULL; // Initialize the pointer to NULL
    shuffled = malloc(len * size);
    if (shuffled == NULL) {
        free(original);
        return 0;
    }
    memcpy(shuffled, L, len * size);
    
    riffle(shuffled, len, size, 10);
    
    for (int i = 0; i < len; i++) {
        int found = 0;
        for (int j = 0; j < len; j++) {
            if (cmp((unsigned char *)original + i * size, (unsigned char *)shuffled + j * size) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            free(original);
            free(shuffled);
            return 0;
        }
    }

    free(original);
    free(shuffled);
    return 1;
}

/**
 * @brief Evaluate the quality of an array of integers.
 *
 * @param numbers The array of integers.
 * @param len The length of the array.
 * @return float The quality of the array.
 */
float quality(int *numbers, int len) {
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if (numbers[i] < numbers[i + 1]) {
            count++;
        }
    }
    return (float)count / (len - 1);
}

/**
 * @brief Calculate the average quality of a shuffled array.
 *
 * @param N The length of the array.
 * @param shuffles The number of shuffles to perform.
 * @param trials The number of trials for the calculation.
 * @return float The average quality of the shuffled array.
 */
float average_quality(int N, int shuffles, int trials) {
    int *numbers = NULL; // Initialize the pointer to NULL
    numbers = (int *)malloc(N * sizeof(int));
    if (numbers == NULL) {
        return 0;
    }
    float total_quality = 0;

    srand(time(NULL));

    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < N; i++) {
            numbers[i] = i;
        }

        riffle(numbers, N, sizeof(int), shuffles);
        total_quality += quality(numbers, N);
    }

    free(numbers);
    return total_quality / trials;
}
   



