#include <stdio.h>
#include <stdbool.h>
#include "beggar.h"

int finished(int *player_sizes, int Nplayers) {
    int count = 0;
    for (int i = 0; i < Nplayers; i++) {
        if (player_sizes[i] == 52) {
            count++;
        }
    }
    return count == Nplayers - 1;
}

int penalty(int card) {
    if (card >= 11 && card <= 14) {
        return 15 - card;
    }
    return 0;
}

void shift_left(int *arr, int *size) {
    for (int i = 1; i < *size; i++) {
        arr[i - 1] = arr[i];
    }
    (*size)--;
}

int take_turn(int *player, int *player_size, int *pile, int *pile_size) {
    int card = player[0];
    shift_left(player, player_size);
    pile[*pile_size] = card;
    (*pile_size)++;

    int pen = penalty(card);
    if (pen) {
        return pen;
    }

    return 0;
}

int beggar(int Nplayers, int *deck, int talkative) {
    int players[Nplayers][52];
    int player_sizes[Nplayers];
    int pile[52];
    int pile_size = 0;
    int turn = 0;

    for (int i = 0; i < Nplayers; i++) {
        player_sizes[i] = 0;
    }

    for (int i = 0; i < 52; i++) {
        players[i % Nplayers][player_sizes[i % Nplayers]++] = deck[i];
    }

    int currentPlayer = 0;
    while (!finished(player_sizes, Nplayers)) {
        turn++;
        if (talkative) {
            printf("Turn %d\n", turn);
        }

        int pen = take_turn(players[currentPlayer], &player_sizes[currentPlayer], pile, &pile_size);

        while (pen > 0 && player_sizes[currentPlayer] > 0) {
            for (int i = 0; i < pen; i++) {
                int new_pen = take_turn(players[currentPlayer], &player_sizes[currentPlayer], pile, &pile_size);
                if (new_pen) {
                    pen = new_pen;
                    i = -1;
                } else {
                    pen--;
                }
            }

            if (pen > 0) {
                break;
            }

            currentPlayer = (currentPlayer - 1 + Nplayers) % Nplayers;
            for (int i = 0; i < pile_size; i++) {
                players[currentPlayer][player_sizes[currentPlayer]++] = pile[i];
            }
            pile_size = 0;
        }

        currentPlayer = (currentPlayer + 1) % Nplayers;
    }

    return turn;
}
