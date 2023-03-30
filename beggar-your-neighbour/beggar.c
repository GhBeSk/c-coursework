#include <stdio.h>
#include <stdlib.h>
#include "shuffle.h"
#include <limits.h>
#include "beggar.h"

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
    int top_card = players[player_index][0];
    for (int i = 0; i < 51; i++) {
        players[player_index][i] = players[player_index][i + 1];
    }
    players[player_index][51] = 0;

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
    int top_card = pile[pile_top - 1];

    printf("Turn %d Top card in pile is ", turn);
    print_card(top_card);
    printf(", so player %d should lay ", current_player);
    
    if (top_card >= 11) {
        printf("%d penalty cards\n", top_card - 10);
    } else {
        printf("a single card\n");
    }

    printf("Pile: ");
    for (int i = 0; i < pile_top; i++) {
        print_card(pile[i]);
        printf(", ");
    }
    printf("\n");

    for (int p = 0; p < Nplayers; p++) {
        if (p == current_player) {
            printf("* ");
        } else {
            printf("  ");
        }
        printf("%d: ", p);
        for (int c = 0; c < 52; c++) {
            if (players[p][c] != 0) {
                print_card(players[p][c]);
                printf(", ");
            }
        }
        printf("\n");
    }
}


int beggar(int Nplayers, int *deck, int talkative) {
    int **players = (int **)malloc(Nplayers * sizeof(int *));
    for (int i = 0; i < Nplayers; i++) {
        players[i] = (int *)calloc(52, sizeof(int));
    }

    for (int i = 0; i < 52; i++) {
        players[i % Nplayers][i / Nplayers] = deck[i];
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
                players[player_index][pile_top - reward + i] = pile[i];
            }
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

