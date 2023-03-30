/**

@file byn.c
@brief Main file for running simulations of the Beggar-Your-Neighbor card game and collecting statistics
This file contains the main function for running simulations of the Beggar-Your-Neighbor card game with varying numbers
of players and collecting statistics on the shortest, longest, and average number of turns it takes to finish the game.
Usage: byn <max_players> <trials>
where max_players is the maximum number of players to simulate for, and trials is the number of trials to run for each number of players.
The output will be written to a file called statistics.txt in the current directory.
*/

#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"

/**

@brief Main function for running simulations of the Beggar-Your-Neighbor card game and collecting statistics

This function reads command line arguments for the maximum number of players and the number of trials to run for each number of players.

It then loops over the range of numbers of players to simulate for and calls the get_statistics function to collect statistics

for the specified number of trials. The statistics are then printed to a file called statistics.txt in the current directory.

@param argc Number of command line arguments

@param argv Array of command line argument strings

@return 0 if the program exits successfully, 1 otherwise
*/

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

