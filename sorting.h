#ifndef SORTING_H
#define SORTING_H

void bubbleSorting(int *tab, int size, SDL_Renderer *renderer);

void insertionSorting(int *tab, int size, SDL_Renderer *renderer);

void selectionSorting(int *tab, int size, SDL_Renderer *renderer);

void quickSorting(int *tab, int low, int high, int size, SDL_Renderer *renderer);


#endif