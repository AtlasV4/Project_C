#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <math.h>

int *generateArray(int size, enum Shuffle random) {
    srand(time(NULL));
    int *tab = malloc(size * sizeof(int));

    if (!tab) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        tab[i] = i+1;
    }

    switch (random) {
        case NOSHUFFLE:
            break;

        case FULLSHUFFLE: {
            for (int i = size - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                int tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        } break;

        case TINYSHUFFLE: {
            int swaps = size / 10;
            if (swaps < 1) swaps = 1;
            for (int k = 0; k < swaps; k++) {
                int i = rand() % size;
                int j = rand() % size;
                if (i == j) {
                    j = (j + 1) % size;
                }
                int tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        } break;
    }

    return tab;
}

void HSVtoRGB(float h, float s, float v, int *r, int *g, int *b) {
    float c = v * s;
    float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
    float m = v - c;
    float r1, g1, b1;

    if      (h < 60)  { r1 = c; g1 = x; b1 = 0; }
    else if (h < 120) { r1 = x; g1 = c; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = c; b1 = x; }
    else if (h < 240) { r1 = 0; g1 = x; b1 = c; }
    else if (h < 300) { r1 = x; g1 = 0; b1 = c; }
    else              { r1 = c; g1 = 0; b1 = x; }

    *r = (int)((r1 + m) * 255);
    *g = (int)((g1 + m) * 255);
    *b = (int)((b1 + m) * 255);
}
