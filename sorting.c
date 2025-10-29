#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sorting.h"
#include "visual.h"

void bubbleSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay)
{
    int abort_sort = 0;
    for (int i = 0; i < size - 1 && !abort_sort; i++) {
        for (int j = 0; j < size - i - 1 && !abort_sort; j++) {
            renderFrame(r, font, *pos, tab, size, j, j+1, -1, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, &abort_sort);

            if (tab[j] > tab[j+1]) {
                int t = tab[j]; tab[j] = tab[j+1]; tab[j+1] = t;
                renderFrame(r, font, *pos, tab, size, j, j+1, -1, delay);
                SDL_Delay(delay);
                handleOverlayEvents(pos, &abort_sort);
            }
        }
    }
}



void insertionSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay)
{
    int abort_sort = 0;
    for (int i = 1; i < size && !abort_sort; i++) {
        int key = tab[i];
        int j = i - 1;

        while (j >= 0 && tab[j] > key && !abort_sort) {
            renderFrame(r, font, *pos, tab, size, j, j+1, -1, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, &abort_sort);

            tab[j+1] = tab[j];
            j--;
            renderFrame(r, font, *pos, tab, size, j, j+1, -1, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, &abort_sort);
        }
        tab[j+1] = key;
        renderFrame(r, font, *pos, tab, size, j+1, -1, -1, delay);
        SDL_Delay(delay);
        handleOverlayEvents(pos, &abort_sort);
    }
}




void selectionSorting(int *tab, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay)
{
    int abort_sort = 0;
    for (int i = 0; i < size - 1 && !abort_sort; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size && !abort_sort; j++) {
            renderFrame(r, font, *pos, tab, size, minIndex, j, -1, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, &abort_sort);
            if (tab[j] < tab[minIndex]) minIndex = j;
        }
        if (minIndex != i) {
            int t = tab[i]; tab[i] = tab[minIndex]; tab[minIndex] = t;
            renderFrame(r, font, *pos, tab, size, i, minIndex, -1, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, &abort_sort);
        }
    }
}

static void quickRec(int *tab, int low, int high, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int *abort_sort, int delay)
{
    if (*abort_sort || low >= high) return;

    int pivotVal = tab[high];
    int i = low - 1;

    for (int j = low; j < high && !*abort_sort; j++) {
        renderFrame(r, font, *pos, tab, size, j, -1, high, delay);
        SDL_Delay(delay);
        handleOverlayEvents(pos, abort_sort);

        if (tab[j] < pivotVal) {
            i++;
            int t = tab[i]; tab[i] = tab[j]; tab[j] = t;
            renderFrame(r, font, *pos, tab, size, i, j, high, delay);
            SDL_Delay(delay);
            handleOverlayEvents(pos, abort_sort);
        }
    }
    int t = tab[i+1]; tab[i+1] = tab[high]; tab[high] = t;
    renderFrame(r, font, *pos, tab, size, i+1, high, i+1, delay);
    SDL_Delay(delay);
    handleOverlayEvents(pos, abort_sort);

    int pi = i + 1;
    quickRec(tab, low, pi - 1, size, r, font, pos, abort_sort, delay);
    quickRec(tab, pi + 1, high, size, r, font, pos, abort_sort, delay);
}

void quickSorting(int *tab, int low, int high, int size, SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, int delay)
{
    int abort_sort = 0;
    quickRec(tab, low, high, size, r, font, pos, &abort_sort, delay);
}





