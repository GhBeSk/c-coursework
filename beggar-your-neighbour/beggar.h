#ifndef BEGGAR_H
#define BEGGAR_H

int finished(int *player_sizes, int Nplayers);
int penalty(int card);
void shift_left(int *arr, int *size);
int take_turn(int *player, int *player_size, int *pile, int *pile_size);
int beggar(int Nplayers, int *deck, int talkative);

#endif // BEGGAR_H

