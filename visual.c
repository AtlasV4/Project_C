#include <SDL2/SDL.h>
#include "visual.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 400;

void drawArray(SDL_Renderer *renderer, int *tab, int size) {
    int gap = SCREEN_WIDTH / size;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < size; i++) {
        SDL_Rect rect;
        rect.x = i * gap;
        rect.w = gap - 1;
        rect.h = (tab[i] * SCREEN_HEIGHT) / size;
        rect.y = SCREEN_HEIGHT - rect.h;

        int r = (tab[i] * 255) / size;
        int g = 0;
        int b = 255 - (tab[i] * 255) / size;

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

