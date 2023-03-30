#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"
#include <limits.h>
#include "beggar.h"

void init_deck(int *deck) {
    for (int i = 0; i < 52; i++) {
        deck[i] = i + 1;
    }
}

void shuffle_deck(int *deck) {
    shuffle(deck, 52, -1); // Use -1 as seed for time-based randomization
}

void print_card(int card) {
    const char *suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    int suit = (card - 1) / 13;
    int rank = (card - 1) % 13;

    printf("%s of %s", ranks[rank], suits[suit]);
}

int finished(int **players, int Nplayers) {
    int finished_count = 0;
    for (int i = 0; i < Nplayers; i++) {
        if (players[i][0] == 0) {
            finished_count++;
        }
    }
    return finished_count == Nplayers - 1;
}

int take_turn(int **players, int *pile, int *pile_top, int *penalty, int player_index) {
    int top_card = players[player_index][1];
    for (int i = 1; i < players[player_index][0]; i++) {
        players[player_index][i] = players[player_index][i + 1];
    }
    players[player_index][players[player_index][0]] = 0;
    players[player_index][0]--;

    pile[*pile_top] = top_card;
    (*pile_top)++;

    if (*penalty > 0) {
        (*penalty)--;
    } else if (top_card > 10) {
        *penalty = 14 - top_card;
        return 0;
    }

    if (*penalty == 0) {
        int reward = *pile_top;
        *pile_top = 0;
        return reward;
    } else {
        return 0;
    }
}

void print_game_state(int turn, int current_player, int *pile, int pile_top, int penalty, int **players, int Nplayers) {
    printf("Turn %d ", turn);
    if (penalty > 0) {
        printf("Top card in pile is %c, so player %d should lay %d penalty cards\n", rankChar(pile[pile_top]), current_player, penalty);
    } else {
        printf("Top card in pile is %c, so player %d should lay a single card\n", rankChar(pile[pile_top]), current_player);
    }

    printf("Pile:");
    for (int i = 0; i <= pile_top; i++) {
        printf(" %c,", rankChar(pile[i]));
    }
    printf("\n");

    for (int i = 0; i < Nplayers; i++) {
        if (i == current_player) {
            printf("* ");
        } else {
            printf("  ");
        }
        printf("%d:", i);
        for (int j = 0; j < players[i][0]; j++) {
            printf(" %c,", rankChar(players[i][j + 1]));
        }
        printf("\n");
    }

    printf("\n"); // Add an empty line between turns for better readability
}

int beggar(int Nplayers, int *deck, int talkative) {
    int **players = (int **)malloc(Nplayers * sizeof(int *));
    for (int i = 0; i < Nplayers; i++) {
        players[i] = (int *)calloc(52, sizeof(int));
        players[i][0] = 52 / Nplayers; // Initialize the number of cards for each player
    }

    for (int i = 0; i < 52; i++) {
        players[i % Nplayers][i / Nplayers + 1] = deck[i];
    }

    int player_index = 0;
    int pile[52];
    int pile_top = 0;
    int penalty = 0;
    int total_turns = 0;

    while (!finished(players, Nplayers)) {
        if (talkative) {
            print_game_state(total_turns, player_index, pile, pile_top, penalty, players, Nplayers);
        }

        int reward = take_turn(players, pile, &pile_top, &penalty, player_index);

        if (reward > 0) {
            for (int i = 0; i < reward; i++) {
                players[player_index][players[player_index][0] + i + 1] = pile[i];
            }
            players[player_index][0] += reward;
            pile_top = 0;
        }

        if (talkative && reward != 0) {
            printf("Player %d takes %d cards\n", player_index + 1, reward);
        }

        total_turns++;

        player_index = (player_index + 1) % Nplayers;
    }

    int winner = -1;
    for (int i = 0; i < Nplayers; i++) {
        if (players[i][0] != 0) {
            winner = i;
            break;
        }
    }

    for (int i = 0; i < Nplayers; i++) {
        free(players[i]);
        players[i] = NULL;
    }
    free(players);
    players = NULL;

    return total_turns;
}

statistics get_statistics(int Nplayers, int games) {
    int *deck = (int *)malloc(52 * sizeof(int));
    init_deck(deck);

    int total_turns = 0;
    int shortest = INT_MAX;
    int longest = 0;

    for (int i = 0; i < games; i++) {
        shuffle_deck(deck);
        int turns = beggar(Nplayers, deck, 0);
        total_turns += turns;

        if (turns < shortest) {
            shortest = turns;
        }
        if (turns > longest) {
            longest = turns;
        }
    }

    statistics stats;
    stats.shortest = shortest;
    stats.longest = longest;
    stats.average = (double)total_turns / games;

    free(deck);

    return stats;
}


