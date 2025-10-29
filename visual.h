#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

typedef enum {
    ALGO_NONE = 0,
    ALGO_BUBBLE,
    ALGO_INSERTION,
    ALGO_SELECTION,
    ALGO_QUICK,
} Algo;

typedef enum {
    MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM
} MenuPosition;

void drawArray(SDL_Renderer *renderer, int *tab, int size, MenuPosition pos, int hiA, int hiB, int pivot);
void renderFrame(SDL_Renderer *r, TTF_Font *font, MenuPosition pos, int *tab, int size, int hiA, int hiB, int pivot, int delay);
void drawMenuOverlay(SDL_Renderer *r, TTF_Font *font, MenuPosition pos, int delay);
void runAlgorithm(SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, Algo algo, int *tab, int N, int delay);
int  handleOverlayEvents(MenuPosition *pos, int *abort_sort);

#endif
