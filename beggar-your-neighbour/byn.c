// byn.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "beggar.h"
#include "byn.h"

Stats statistics(int Nplayers, int games) {
    Stats stats = {INT_MAX, 0, 0.0};

    int deck[52];
    for (int i = 0; i < 52; i++) {
        deck[i] = i % 13 + 2;
    }

    int total_turns = 0;
    for (int game = 0; game < games; game++) {
        shuffle(deck, 52, -1);
        int turns = beggar(Nplayers, deck, 0);

        if (turns < stats.shortest) {
            stats.shortest = turns;
        }
        if (turns > stats.longest) {
            stats.longest = turns;
        }

        total_turns += turns;
    }

    stats.average = (double)total_turns / games;
    return stats;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <max_players> <number_of_trials>\n", argv[0]);
        return 1;
    }

    int max_players = atoi(argv[1]);
    int trials = atoi(argv[2]);

    FILE *file = fopen("statistics.txt", "w");

    fprintf(file, "Players\tShortest\tLongest\tAverage\n");
    for (int Nplayers = 2; Nplayers <= max_players; Nplayers++) {
        Stats stats = statistics(Nplayers, trials);
        fprintf(file, "%d\t%d\t%d\t%.2f\n", Nplayers, stats.shortest, stats.longest, stats.average);
    }

    fclose(file);
    printf("Statistics written to 'statistics.txt'.\n");

    return 0;
}
