// byn.h
#ifndef BYN_H
#define BYN_H

typedef struct Stats {
    int shortest;
    int longest;
    double average;
} Stats;

Stats statistics(int Nplayers, int games);

#endif
