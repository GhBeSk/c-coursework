#ifndef BEGGAR_H
#define BEGGAR_H

typedef struct {
    int shortest;
    int longest;
    double average;
} statistics;

// Initialize a deck of cards
void init_deck(int *deck);
void shuffle_deck(int *deck);
void print_card(int card);
int finished(int **players, int Nplayers);
int *take_turn(int **player, int **pile, int *pile_top, int penalty);
void print_game_state(int turn, int current_player, int *pile, int pile_top, int penalty, int **players, int Nplayers);
int beggar(int Nplayers, int *deck, int talkative);


// Get statistics for the Beggar-My-Neighbor game
statistics get_statistics(int Nplayers, int games);

#endif // BEGGAR_H
