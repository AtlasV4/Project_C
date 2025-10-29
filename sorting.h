#ifndef SORTING_H
#define SORTING_H

#include "visual.h"

void bubbleSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay);
void insertionSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay);
void selectionSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay);
void quickSorting(int *tab, int low, int high, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay);


#endif