#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

enum RandomMode {
    TINYSHUFFLE,
    FULLSHUFFLE,
    NOSHUFFLE
};

int *generateArray(int size, enum RandomMode mode);

#endif