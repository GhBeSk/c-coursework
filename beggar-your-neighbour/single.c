#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "shuffle.h"

#define DECK_SIZE 52

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <number_of_players>\n", argv[0]);
        return 1;
    }

    int Nplayers = atoi(argv[1]);
    if (Nplayers < 2) {
        printf("Number of players must be at least 2.\n");
        return 1;
    }

    int deck[DECK_SIZE];
    int i;
    for (i = 0; i < DECK_SIZE; i++) {
        deck[i] = i % 13 + 2;
    }

    shuffle(deck, DECK_SIZE, -1);

    int turns = beggar(Nplayers, deck, 1);

    printf("\nGame finished in %d turns.\n", turns);

    return 0;
}
