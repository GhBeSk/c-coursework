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
    const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9","Jack", "Queen", "King", "Ace"};

    int suit = (card - 1) / 13;
    int rank = (card - 1) % 13;

    printf("%s of %s", ranks[rank], suits[suit]);
}

char rankChar(int card) {
    const char *ranks = "23456789JQKA";
    int rank = (card - 1) % 13;
    return ranks[rank];
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

int reward(int **players, int *pile, int pile_top, int current_player) {
    int reward_cards[52] = {0};
    int reward_top = 0;

    if (pile_top == 0) {
        return reward_top;
    }

    int top_card = pile[pile_top - 1];
    int penalty = 0;
    for (int i = 0; i < 52; i++) {
        if (players[current_player][i] == 0) {
            break;
        }
        int card = players[current_player][i];
        players[current_player][i] = 0;
        if (card == top_card) {
            penalty = 0;
            continue;
        }
        if (penalty > 0) {
            penalty--;
            continue;
        }
        reward_cards[reward_top++] = card;
        if (card > 10) {
            penalty = 14 - card;
        }
    }

    for (int i = 0; i < reward_top; i++) {
        pile[pile_top++] = reward_cards[i];
    }

    return reward_top;
}

int take_turn(int **players, int *pile, int *pile_top, int *penalty, int player_index, int Nplayers) {
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
        int reward_top = reward(players, pile, *pile_top, player_index);
        int reward[Nplayers];
        for (int i = 0; i < Nplayers; i++) {
            reward[i] = 0;
        }

        if (reward_top > 0) {
            int next_player = (player_index + 1) % Nplayers;
            while (players[next_player][0] == 0) {
                next_player = (next_player + 1) % Nplayers;
            }

            for (int i = 0; i < reward_top; i++) {
                int j = 0;
                while (players[next_player][j] != 0) {
                    j++;
                }
                players[next_player][j] = pile[i];
                reward[next_player]++;
            }
            *pile_top = 0;
            *penalty = 0;
        }

        return reward[player_index];
    } else {
        return 0;
    }
}

void print_game_state(int turn, int current_player, int *pile, int pile_top, int penalty, int **players, int Nplayers) {
    printf("Turn %d ", turn);
    if (pile_top == 0) {
        printf("Pile now empty so player %d to lay a single card\n", current_player);
    } else if (penalty > 0) {
        printf("Top card in pile is %c, so player %d should lay %d penalty cards\n", rankChar(pile[pile_top - 1]), current_player, penalty);
    } else {
        printf("Top card in pile is %c, so player %d should lay a single card\n", rankChar(pile[pile_top - 1]), current_player);
    }

    printf("Pile:");
    for (int i = 0; i < pile_top; i++) {
        printf(" %c,", rankChar(pile[i]));
    }
    printf("\n");

    for (int i = 0; i < Nplayers; i++) {
        printf("%d:", i);
        for (int j = 0; j < 52 && players[i][j] != 0; j++) {
            printf(" %c,", rankChar(players[i][j]));
        }
        printf("\n");
    }
    printf("\n");
}

int beggar(int Nplayers, int *deck, int talkative) {
    int turn = 0;
    int current_player = 0;
    int winner = -1;

    int **players = malloc(Nplayers * sizeof(int *));
    for (int i = 0; i < Nplayers; i++) {
        players[i] = calloc(52, sizeof(int));
    }

    for (int i = 0; i < 52; i++) {
        players[i % Nplayers][i / Nplayers] = deck[i];
    }

    int pile[52] = {0};
    int pile_top = 0;
    int penalty = 0;

    while (!finished(players, Nplayers)) {
        turn++;

        int reward = take_turn(players, pile, &pile_top, &penalty, current_player, Nplayers);
        if (reward > 0) {
            int next_player = (current_player + 1) % Nplayers;
            while (players[next_player][0] == 0) {
                next_player = (next_player + 1) % Nplayers;
            }

            for (int i = 0; i < reward; i++) {
                int j = 0;
                while (players[next_player][j] != 0) {
                    j++;
                }
                players[next_player][j] = pile[i];
            }
            pile_top = 0;
            penalty = 0;
        }

        if (talkative) {
            print_game_state(turn, current_player, pile, pile_top, penalty, players, Nplayers);
        }

        do {
            current_player = (current_player + 1) % Nplayers;
        } while (players[current_player][0] == 0);
    }

    for (int i = 0; i < Nplayers; i++) {
        if (players[i][0] != 0) {
            winner = i;
        }
        free(players[i]);
    }
    free(players);

    return winner;
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
