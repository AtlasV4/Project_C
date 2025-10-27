#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

enum RandomMode { TINYSHUFFLE, FULLSHUFFLE, NOSHUFFLE };

int *generateArray(int size, enum RandomMode random) {
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
