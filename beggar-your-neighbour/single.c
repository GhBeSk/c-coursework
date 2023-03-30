/**
@file single.c
@brief Implements a single game of beggar-my-neighbour with a user-specified number of players.
The program takes one command-line argument specifying the number of players, creates a deck of cards, shuffles it,
and starts a game of beggar-my-neighbour with the specified number of players. The game proceeds until a winner is
declared, and the program prints out the winner and the total number of turns taken to reach the end of the game.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"

/**

@brief Main function that implements a single game of beggar-my-neighbour.

@param argc The number of command-line arguments.

@param argv An array of strings containing the command-line arguments.

@return 0 if the program runs successfully, and a non-zero integer otherwise.
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_players>\n", argv[0]);
        return 1;
    }

    int Nplayers = atoi(argv[1]);
    if (Nplayers <= 0 || Nplayers > 52) {
        printf("Invalid number of players. Must be between 1 and 52.\n");
        return 1;
    }

    int deck[52] = {0};
    init_deck(deck);
    shuffle_deck(deck);

    printf("Starting game with %d players\n", Nplayers);

    int turn_counter = 0;
    int winner = -1;

    while (winner == -1) {
        turn_counter++;
        winner = beggar(Nplayers, deck, 0);
    }

    printf("Winner: Player %d\n", winner);
    printf("Game over! Total turns: %d\n", turn_counter);

    return 0;
}

