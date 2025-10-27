#include <SDL2/SDL.h>
#include "sorting.h"
#include "visual.h"

void bubbleSorting(int *tab, int size, SDL_Renderer *renderer) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;

                drawArray(renderer, tab, size);
                SDL_Delay(5); 
            }
        }
    }
}

void insertionSorting(int *tab, int size, SDL_Renderer *renderer) {
    for (int i = 1; i < size; i++) {
        int key = tab[i];
        int j = i - 1;

        while (j >= 0 && tab[j] > key) {
            tab[j + 1] = tab[j];
            j--;

            drawArray(renderer, tab, size);
            SDL_Delay(5);
        }

        tab[j + 1] = key;

        drawArray(renderer, tab, size);
        SDL_Delay(10);
    }
}


void selectionSorting(int *tab, int size, SDL_Renderer *renderer) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (tab[j] < tab[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = tab[i];
            tab[i] = tab[minIndex];
            tab[minIndex] = temp;

            drawArray(renderer, tab, size);
            SDL_Delay(5);
        }
    }
}


void quickSorting(int *tab, int low, int high, int size, SDL_Renderer *renderer) {
    if (low < high) {
        int pivot = tab[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (tab[j] < pivot) {
                i++;
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;

                drawArray(renderer, tab, size);
                SDL_Delay(5);
            }
        }

        int temp = tab[i + 1];
        tab[i + 1] = tab[high];
        tab[high] = temp;

        drawArray(renderer, tab, size);
        SDL_Delay(5);

        int pi = i + 1;

        quickSorting(tab, low, pi - 1, size, renderer);
        quickSorting(tab, pi + 1, high, size, renderer);
    }
}



