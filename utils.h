#ifndef UTILS_H
#define UTILS_H

typedef enum Shuffle {
    TINYSHUFFLE,
    FULLSHUFFLE,
    NOSHUFFLE
} Shuffle;

int *generateArray(int size, Shuffle mode);

void HSVtoRGB(float h, float s, float v, int *r, int *g, int *b);

#endif