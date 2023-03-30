#ifndef BEGGAR_H
#define BEGGAR_H

typedef struct {
    int shortest;
    int longest;
    double average;
} statistics;

// Initialize a deck of cards
void init_deck(int *deck);

// Shuffle a deck of cards
void shuffle_deck(int *deck);

// Print a single card
void print_card(int card);

// Determine if the game is finished
int finished(int **players, int Nplayers);

// Take a turn in the game
int take_turn(int **players, int *pile, int *pile_top, int *penalty, int player_index);

// Print the current game state
void print_game_state(int turn, int current_player, int *pile, int pile_top, int penalty, int **players, int Nplayers);

// Play the Beggar-My-Neighbor game and return the total number of turns
int beggar(int Nplayers, int *deck, int talkative);

// Get statistics for the Beggar-My-Neighbor game
statistics get_statistics(int Nplayers, int games);

#endif // BEGGAR_H
