#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "shuffle.h"
#include "beggar.h"

void init_deck(int *deck) {
    for (int i = 0; i < 52; i++) {
        deck[i] = i % 13 + 1;
    }
}

void print_card(int card) {
    const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    printf("%s", ranks[card - 1]);
}

void shuffle_deck(int *deck) {
    shuffle(deck, 52, -1); // Use -1 as seed for time-based randomization
}

int finished(int **players, int Nplayers) {
    int finished_count = 0;
    for (int i = 0; i < Nplayers; i++) {
        if (players[i][0] == 0) {
            finished_count++;
        }
    }

    if (finished_count == Nplayers - 1) {
        return 1;
    } else {
        return 0;
    }
}

int *take_turn(int **player, int **pile, int *pile_top, int penalty) {
    int *reward = NULL;
    int cards_to_lay = penalty ? penalty : 1;

    for (int i = 0; i < cards_to_lay; i++) {
        if ((*player)[0] == 0) {
            break;
        }

        (*pile)[*pile_top] = (*player)[1];
        for (int j = 1; j < (*player)[0]; j++) {
            (*player)[j] = (*player)[j + 1];
        }
        (*player)[0]--;
        (*pile_top)++;

        if (penalty && ((*pile)[*pile_top - 1] > 10)) {
            return NULL;
        }
    }

    if (penalty) {
        int reward_size = *pile_top + 1;
        reward = (int *)malloc(reward_size * sizeof(int));
        if (reward == NULL) {
            printf("Error: unable to allocate memory for reward\n");
            exit(1);
        }
        reward[0] = *pile_top;
        for (int i = 0; i < *pile_top; i++) {
            reward[i + 1] = (*pile)[i];
        }
        *pile_top = 0;
    }

    return reward;
}



void print_game_state(int turn, int current_player, int *pile, int pile_top, int penalty, int **players, int Nplayers) {
    printf("Turn %d ", turn);
    if (penalty > 0) {
        printf("Top card is ");
        print_card(pile[pile_top - 1]);
        printf(", so player %d should lay %d penalty cards\n", current_player, penalty);
    } else {
        printf("Player %d to lay a single card\n", current_player);
    }

    printf("Pile:");
    for (int i = 0; i < pile_top; i++) {
        printf(" ");
        print_card(pile[i]);
        if (i < pile_top - 1) {
            printf(",");
        }
    }
    printf("\n");

    for (int i = 0; i < Nplayers; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= players[i][0]; j++) {
            print_card(players[i][j]);
            if (j < players[i][0]) {
                printf(", "); }
        }
        if (i == current_player) {
            printf(" *");
        }
        printf("\n");
    }
    printf("\n");
}

int beggar(int Nplayers, int *deck, int talkative) {
    int **players = (int **)malloc(Nplayers * sizeof(int *));
    for (int i = 0; i < Nplayers; i++) {
        players[i] = (int *)malloc(53 * sizeof(int));
        players[i][0] = 0;
    }

    for (int i = 0; i < 52; i++) {
        int player_idx = i % Nplayers;
        int player_hand_size = players[player_idx][0];
        players[player_idx][player_hand_size + 1] = deck[i];
        players[player_idx][0]++;
    }

    int *pile = (int *)malloc(53 * sizeof(int));
    int pile_top = 0;

    int turn = 1;
    int current_player = 0;
    int penalty = 0;

    while (!finished(players, Nplayers)) {
        int *reward = take_turn(&players[current_player], &pile, &pile_top, penalty);

        if (talkative) {
            print_game_state(turn, current_player, pile, pile_top, penalty, players, Nplayers);
        }

        if (reward) {
            int prev_player = (current_player + Nplayers - 1) % Nplayers;
            for (int i = 0; i < reward[0]; i++) {
                players[prev_player][players[prev_player][0] + 1] = reward[i + 1];
                players[prev_player][0]++;
            }
            free(reward);
            pile_top = 0;
            penalty = 0;
        } else if (pile_top > 0) {
            penalty = pile[pile_top - 1] > 10 ? pile[pile_top - 1] - 10 : 0;
        }

        current_player = (current_player + 1) % Nplayers;
        turn++;
    }

    for (int i = 0; i < Nplayers; i++) {
        free(players[i]);
    }
    free(players);
    free(pile);

    return turn - 1;
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
