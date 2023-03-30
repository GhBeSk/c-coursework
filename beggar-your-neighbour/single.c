#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"

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

    int winner = beggar(Nplayers, deck, 0);
    int total_turns = (Nplayers - 1) * winner;

    printf("Winner: Player %d\n", winner );

    printf("Game over! Total turns: %d\n", total_turns);

    return 0;
}

