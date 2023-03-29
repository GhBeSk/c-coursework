#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

// Add the statistics struct and get_statistics function here

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <max_players> <trials>\n", argv[0]);
        return 1;
    }

    int max_players = atoi(argv[1]);
    int trials = atoi(argv[2]);

    FILE *output_file = fopen("statistics.txt", "w");
    if (output_file == NULL) {
        perror("Error opening statistics.txt");
        return 1;
    }

    for (int players = 2; players <= max_players; players++) {
        statistics stats = get_statistics(players, trials);
        fprintf(output_file, "Players: %d | Shortest: %d | Longest: %d | Average: %.2f\n", players, stats.shortest, stats.longest, stats.average);
    }

    fclose(output_file);

    return 0;
}

